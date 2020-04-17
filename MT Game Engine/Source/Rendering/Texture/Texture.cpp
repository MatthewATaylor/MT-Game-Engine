#include "Rendering/Texture/Texture.h"

namespace mtge {
	//Private
	Texture *Texture::atlas = nullptr;
	Texture *Texture::skybox = nullptr;

	void Texture::setTextureWrap_GL(TextureWrapSetting textureWrap, GLint &textureWrap_GL) {
		switch (textureWrap) {
		case TextureWrapSetting::REPEAT:
			textureWrap_GL = GL_REPEAT;
			break;
		case TextureWrapSetting::REPEAT_MIRRORED:
			textureWrap_GL = GL_MIRRORED_REPEAT;
			break;
		case TextureWrapSetting::EDGE_CLAMP:
			textureWrap_GL = GL_CLAMP_TO_EDGE;
			break;
		case TextureWrapSetting::BORDER_CLAMP:
			textureWrap_GL = GL_CLAMP_TO_BORDER;
		}
	}
	void Texture::setTextureFilter_GL(TextureFilterSetting textureFilter, GLint &textureFilter_GL) {
		switch (textureFilter) {
		case TextureFilterSetting::NEAREST:
			textureFilter_GL = GL_NEAREST;
			break;
		case TextureFilterSetting::LINEAR:
			textureFilter_GL = GL_LINEAR;
		}
	}
	void Texture::setColorFormat_GL(TextureColorSetting colorFormat, GLint &colorFormat_GL) {
		switch (colorFormat) {
		case TextureColorSetting::RGB:
			colorFormat_GL = GL_RGB;
			break;
		case TextureColorSetting::RGBA:
			colorFormat_GL = GL_RGBA;
		}
	}
	void Texture::setTextureSettings_GL_2D(TextureWrapSetting textureWrapX, TextureWrapSetting textureWrapY, TextureFilterSetting textureFilterMin, TextureFilterSetting textureFilterMag, TextureColorSetting colorFormat) {
		setTextureWrap_GL(textureWrapX, textureSettings_GL_2D.textureWrapX);
		setTextureWrap_GL(textureWrapY, textureSettings_GL_2D.textureWrapY);

		setTextureFilter_GL(textureFilterMin, textureSettings_GL_2D.textureFilterMin);
		setTextureFilter_GL(textureFilterMag, textureSettings_GL_2D.textureFilterMag);

		setColorFormat_GL(colorFormat, textureSettings_GL_2D.colorFormat);
	}
	void Texture::setTextureSettings_GL_3D(TextureWrapSetting textureWrapX, TextureWrapSetting textureWrapY, TextureWrapSetting textureWrapZ, TextureFilterSetting textureFilterMin, TextureFilterSetting textureFilterMag, TextureColorSetting colorFormat) {
		setTextureWrap_GL(textureWrapX, textureSettings_GL_3D.textureWrapX);
		setTextureWrap_GL(textureWrapY, textureSettings_GL_3D.textureWrapY);
		setTextureWrap_GL(textureWrapZ, textureSettings_GL_3D.textureWrapZ);

		setTextureFilter_GL(textureFilterMin, textureSettings_GL_3D.textureFilterMin);
		setTextureFilter_GL(textureFilterMag, textureSettings_GL_3D.textureFilterMag);

		setColorFormat_GL(colorFormat, textureSettings_GL_3D.colorFormat);
	}
	void Texture::load2D(std::string textureFile, TextureWrapSetting textureWrapX, TextureWrapSetting textureWrapY, TextureFilterSetting textureFilterMin, TextureFilterSetting textureFilterMag, TextureColorSetting colorFormat) {
		setTextureSettings_GL_2D(textureWrapX, textureWrapY, textureFilterMin, textureFilterMag, colorFormat);

		//Setup/Bind Texture
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		//Set Texture Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureSettings_GL_2D.textureWrapX);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureSettings_GL_2D.textureWrapY);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureSettings_GL_2D.textureFilterMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureSettings_GL_2D.textureFilterMag);

		//Load Texture
		stbi_set_flip_vertically_on_load(true);
		int textureWidth, textureHeight, numColorChannels;
		unsigned char *data = stbi_load(textureFile.c_str(), &textureWidth, &textureHeight, &numColorChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, textureSettings_GL_2D.colorFormat, textureWidth, textureHeight, 0, textureSettings_GL_2D.colorFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "ERROR [FUNCTION: load2D]: TEXTURE FAILED TO LOAD" << std::endl << std::endl;
		}
		stbi_image_free(data);

		this->target = GL_TEXTURE_2D;
	}
	void Texture::loadCubemap(std::string textureFiles[6], TextureWrapSetting textureWrapX, TextureWrapSetting textureWrapY, TextureWrapSetting textureWrapZ, TextureFilterSetting textureFilterMin, TextureFilterSetting textureFilterMag, TextureColorSetting colorFormat) {
		setTextureSettings_GL_3D(textureWrapX, textureWrapY, textureWrapZ, textureFilterMin, textureFilterMag, colorFormat);

		//Setup/Bind Texture
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		//Set Texture Parameters
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, textureSettings_GL_3D.textureWrapX);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, textureSettings_GL_3D.textureWrapY);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, textureSettings_GL_3D.textureWrapZ);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, textureSettings_GL_3D.textureFilterMin);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, textureSettings_GL_3D.textureFilterMag);

		//Load Texture
		stbi_set_flip_vertically_on_load(false);
		int textureWidth, textureHeight, numColorChannels;
		for (unsigned int i = 0; i < 6; i++) {
			unsigned char *data = stbi_load(textureFiles[i].c_str(), &textureWidth, &textureHeight, &numColorChannels, 0);
			if (data) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, textureSettings_GL_3D.colorFormat, textureWidth, textureHeight, 0, textureSettings_GL_3D.colorFormat, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
			}
			else {
				std::cout << "ERROR [FUNCTION: loadCubemap]: TEXTURE FAILED TO LOAD" << std::endl << std::endl;
			}
			stbi_image_free(data);
		}

		this->target = GL_TEXTURE_CUBE_MAP;
	}
	void Texture::setUniform(Shader* shader, unsigned int location, int textureNum) {
		shader->useProgram();
		shader->setIntUniform(location, textureNum);
	}
	void Texture::activate(GLenum textureNum) {
		glActiveTexture(textureNum);
		glBindTexture(target, textureID);
	}

	//Public
	void Texture::loadTextureAtlas(std::string textureFile, TextureWrapSetting textureWrapX, TextureWrapSetting textureWrapY, TextureFilterSetting textureFilterMin, TextureFilterSetting textureFilterMag, TextureColorSetting colorFormat) {
		atlas = new Texture;
		atlas->load2D(textureFile, textureWrapX, textureWrapY, textureFilterMin, textureFilterMag, colorFormat);
		if (!Shader::getTexturedShapePtr()) {
			std::cout << "ERROR [FUNCTION: loadTextureAtlas]: UNINITIALIZED SHAPE SHADER" << std::endl << std::endl;
			return;
		}
		atlas->setUniform(Shader::getTexturedShapePtr(), Shader::getTexturedShapePtr()->getUniformLocation("texture1"), 0);
		atlas->activate(GL_TEXTURE0);
	}
	void Texture::loadSkybox(SkyboxTextureContainer *textureContainer, TextureWrapSetting textureWrapX, TextureWrapSetting textureWrapY, TextureWrapSetting textureWrapZ, TextureFilterSetting textureFilterMin, TextureFilterSetting textureFilterMag, TextureColorSetting colorFormat) {
		skybox = new Texture;
		skybox->loadCubemap(textureContainer->files, textureWrapX, textureWrapY, textureWrapZ, textureFilterMin, textureFilterMag, colorFormat);
		if (!Shader::getSkyboxPtr()) {
			std::cout << "ERROR [FUNCTION: loadSkybox]: UNINITIALIZED SKYBOX SHADER" << std::endl << std::endl;
			return;
		}
		skybox->setUniform(Shader::getSkyboxPtr(), Shader::getSkyboxPtr()->getUniformLocation("skybox"), 0);
		skybox->activate(GL_TEXTURE0);
	}
	Texture *Texture::getAtlasPtr() {
		return atlas;
	}
	Texture *Texture::getSkyboxPtr() {
		return skybox;
	}
	void Texture::freeResources() {
		if (atlas) {
			delete atlas;
		}
		if (skybox) {
			delete skybox;
		}
	}
}