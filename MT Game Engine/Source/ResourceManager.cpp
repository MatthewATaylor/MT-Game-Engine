#include "ResourceManager.h"

namespace mtge {
	//Private
	Shader *ResourceManager::shapeShader = nullptr;
	Shader *ResourceManager::skyboxShader = nullptr;
	Texture *ResourceManager::textureAtlas = nullptr;
	Texture *ResourceManager::skyboxTexture = nullptr;

	//Public
	bool ResourceManager::startGLFW() {
		if (!glfwInit()) {
			std::cout << "ERROR [FUNCTION: startGLFW]: GLFW FAILED TO INITIALIZE" << std::endl << std::endl;
			return 1;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, DEFAULT_MAJOR_GL);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, DEFAULT_MINOR_GL);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return 0;
	}
	bool ResourceManager::startGLFW(int majorOpenGLVersion, int minorOpenGLVersion) {
		if (!glfwInit()) {
			std::cout << "ERROR [FUNCTION: startGLFW]: GLFW FAILED TO INITIALIZE" << std::endl << std::endl;
			return 1;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorOpenGLVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorOpenGLVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return 0;
	}
	bool ResourceManager::startGLEW() {
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			std::cout << "ERROR [FUNCTION: startGLEW]: GLEW FAILED TO INITIALIZE" << std::endl << std::endl;
			glfwTerminate();
			return 1;
		}
		return 0;
	}
	void ResourceManager::loadShaders(const char *shapeVertexShaderPath, const char *shapeFragmentShaderPath, const char *skyboxVertexShaderPath, const char *skyboxFragmentShaderPath) {
		shapeShader = new Shader(shapeVertexShaderPath, shapeFragmentShaderPath);
		skyboxShader = new Shader(skyboxVertexShaderPath, skyboxFragmentShaderPath);
	}
	void ResourceManager::loadTextureAtlas(const char* textureFile, TextureWrapSetting textureWrapX, TextureWrapSetting textureWrapY, TextureFilterSetting textureFilterMin, TextureFilterSetting textureFilterMag, TextureColorSetting colorFormat) {
		textureAtlas = new Texture;
		textureAtlas->load2D(textureFile, textureWrapX, textureWrapY, textureFilterMin, textureFilterMag, colorFormat);
		if (shapeShader == nullptr) {
			std::cout << "ERROR [FUNCTION: loadTextureAtlas]: UNINITIALIZED SHAPE SHADER" << std::endl << std::endl;
			return;
		}
		textureAtlas->setUniform(shapeShader, shapeShader->getUniformLocation("texture1"), 0);
		textureAtlas->activate(GL_TEXTURE0);
	}
	void ResourceManager::loadSkybox(const std::string FOLDER_NAME, TextureWrapSetting textureWrapX, TextureWrapSetting textureWrapY, TextureWrapSetting textureWrapZ, TextureFilterSetting textureFilterMin, TextureFilterSetting textureFilterMag, TextureColorSetting colorFormat) {
		skyboxTexture = new Texture;
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
		skyboxTexture->loadCubemap(skyboxTexturesChar, textureWrapX, textureWrapY, textureWrapZ, textureFilterMin, textureFilterMag, colorFormat);
		if (skyboxShader == nullptr) {
			std::cout << "ERROR [FUNCTION: loadSkybox]: UNINITIALIZED SKYBOX SHADER" << std::endl << std::endl;
			return;
		}
		skyboxTexture->setUniform(skyboxShader, skyboxShader->getUniformLocation("skybox"), 0);
		skyboxTexture->activate(GL_TEXTURE0);
	}
	void ResourceManager::freeResources() {
		delete shapeShader;
		delete skyboxShader;
		delete textureAtlas;
		delete skyboxTexture;
		glfwTerminate();
	}
	Shader *ResourceManager::getShapeShaderPtr() {
		return shapeShader;
	}
	Shader *ResourceManager::getSkyboxShaderPtr() {
		return skyboxShader;
	}
	Texture *ResourceManager::getTextureAtlasPtr() {
		return textureAtlas;
	}
	Texture *ResourceManager::getSkyboxTexturePtr() {
		return skyboxTexture;
	}
}