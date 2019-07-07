#include "Texture.h"

namespace mtge {
	//Public
	void Texture::load2D(const char* textureFile, GLenum target, GLint textureParamX, GLint textureParamY, GLint textureParamMin, GLint textureParamMag, GLenum colorFormat, GLenum totalChannels) {
		//Setup/Bind Texture
		glGenTextures(1, &textureID);
		glBindTexture(target, textureID);

		//Set Texture Parameters
		glTexParameteri(target, GL_TEXTURE_WRAP_S, textureParamX);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, textureParamY);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, textureParamMin);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, textureParamMag);

		//Load Texture
		stbi_set_flip_vertically_on_load(true);
		int textureWidth, textureHeight, numColorChannels;
		unsigned char *data = stbi_load(textureFile, &textureWidth, &textureHeight, &numColorChannels, 0);
		if (data) {
			glTexImage2D(target, 0, colorFormat, textureWidth, textureHeight, 0, totalChannels, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(target);
		}
		else {
			std::cout << "ERROR: TEXTURE FAILED TO LOAD" << std::endl;
		}
		stbi_image_free(data);

		this->target = target;
	}
	void Texture::loadCubemap(const char *textureFiles[], GLenum target, GLint textureParamX, GLint textureParamY, GLint textureParamZ, GLint textureParamMin, GLint textureParamMag, GLenum colorFormat, GLenum totalChannels) {
		//Setup/Bind Texture
		glGenTextures(1, &textureID);
		glBindTexture(target, textureID);

		//Set Texture Parameters
		glTexParameteri(target, GL_TEXTURE_WRAP_S, textureParamX);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, textureParamY);
		glTexParameteri(target, GL_TEXTURE_WRAP_R, textureParamZ);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, textureParamMin);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, textureParamMag);

		//Load Texture
		stbi_set_flip_vertically_on_load(false);
		int textureWidth, textureHeight, numColorChannels;
		for (unsigned int i = 0; i < 6; i++) {
			unsigned char *data = stbi_load(textureFiles[i], &textureWidth, &textureHeight, &numColorChannels, 0);
			if (data) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, colorFormat, textureWidth, textureHeight, 0, totalChannels, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(target);
			}
			else {
				std::cout << "ERROR: TEXTURE FAILED TO LOAD" << std::endl;
			}
			stbi_image_free(data);
		}

		this->target = target;
	}
	void Texture::loadSkybox(const std::string FOLDER_NAME, GLenum target, GLint textureParamX, GLint textureParamY, GLint textureParamZ, GLint textureParamMin, GLint textureParamMag, GLenum colorFormat, GLenum totalChannels) {
		std::string skyTexturesString[6] = {
			"skyFront.tga",
			"skyBack.tga",
			"skyUp.tga",
			"skyDown.tga",
			"skyRight.tga",
			"skyLeft.tga"
		};
		for (unsigned int i = 0; i < 6; i++) {
			std::string skyTextureFullPath = "Resources/Textures/" + FOLDER_NAME + "/";
			skyTexturesString[i] = skyTextureFullPath + skyTexturesString[i];
		}
		const char *skyboxTexturesChar[6];
		for (unsigned int i = 0; i < 6; i++) {
			skyboxTexturesChar[i] = skyTexturesString[i].c_str();
		}
		loadCubemap(skyboxTexturesChar, target, textureParamX, textureParamY, textureParamZ, textureParamMin, textureParamMag, colorFormat, totalChannels);
	}
	void Texture::setUniform(Shader* shader, unsigned int location, int textureNum) {
		shader->useProgram();
		shader->setIntUniform(location, textureNum);
	}
	void Texture::activate(GLenum textureNum) {
		glActiveTexture(textureNum);
		glBindTexture(target, textureID);
	}
}