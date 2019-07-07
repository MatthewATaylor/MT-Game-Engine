#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

namespace mtge {
	class ResourceManager {
	public:
		static Shader *shapeShader;
		static Shader *skyboxShader;

		static bool startGLFW(int majorOpenGLVersion, int minorOpenGLVersion);
		static bool initWindow(GLFWwindow **window, const char *windowTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
		static bool startGLEW();
		static void initMTGE(const char *shapeVertexShaderPath, const char *shapeFragmentShaderPath, const char *skyboxVertexShaderPath, const char *skyboxFragmentShaderPath);
		static void freeResources();
	};
}