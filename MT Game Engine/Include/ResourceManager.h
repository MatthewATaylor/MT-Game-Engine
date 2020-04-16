#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Rendering/Shader.h"

namespace mtge {
	class ResourceManager {
	private:
		static const int DEFAULT_MAJOR_GL = 3;
		static const int DEFAULT_MINOR_GL = 3;

		static Shader *shapeShader;
		static Shader *skyboxShader;

	public:
		static bool startGLFW();
		static bool startGLFW(int majorOpenGLVersion, int minorOpenGLVersion);
		static bool startGLEW();
		static void loadShaders(const char *shapeVertexShaderPath, const char *shapeFragmentShaderPath, const char *skyboxVertexShaderPath, const char *skyboxFragmentShaderPath);
		static void freeResources();

		static Shader *getShapeShaderPtr();
		static Shader *getSkyboxShaderPtr();
	};
}