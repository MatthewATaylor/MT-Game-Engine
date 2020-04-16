#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Rendering/Shader.h"
#include "Rendering/Texture/Texture.h"

namespace mtge {
	class ResourceManager {
	private:
		static const int DEFAULT_MAJOR_GL = 3;
		static const int DEFAULT_MINOR_GL = 3;

		static Shader *shapeShader;
		static Shader *skyboxShader;

		static Texture *textureAtlas;
		static Texture *skyboxTexture;

	public:
		static bool startGLFW();
		static bool startGLFW(int majorOpenGLVersion, int minorOpenGLVersion);
		static bool startGLEW();
		static void loadShaders(const char *shapeVertexShaderPath, const char *shapeFragmentShaderPath, const char *skyboxVertexShaderPath, const char *skyboxFragmentShaderPath);
		static void loadTextureAtlas(const char* textureFile, TextureWrapSetting textureWrapX, TextureWrapSetting textureWrapY, TextureFilterSetting textureFilterMin, TextureFilterSetting textureFilterMag, TextureColorSetting colorFormat);
		static void loadSkybox(const std::string FOLDER_NAME, TextureWrapSetting textureWrapX, TextureWrapSetting textureWrapY, TextureWrapSetting textureWrapZ, TextureFilterSetting textureFilterMin, TextureFilterSetting textureFilterMag, TextureColorSetting colorFormat);
		static void freeResources();

		static Shader *getShapeShaderPtr();
		static Shader *getSkyboxShaderPtr();

		static Texture *getTextureAtlasPtr();
		static Texture *getSkyboxTexturePtr();
	};
}