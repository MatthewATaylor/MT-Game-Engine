#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

namespace mtge {
	class ResourceManager {
	private:
		static const int DEFAULT_MAJOR_GL = 3;
		static const int DEFAULT_MINOR_GL = 3;

		static Shader *shapeShader;
		static Shader *skyboxShader;

		static bool startGLFW(int majorOpenGLVersion, int minorOpenGLVersion);
		static bool initWindow(GLFWwindow **window, const char *windowTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
		static bool startGLEW();
		static void loadShaders(const char *shapeVertexShaderPath, const char *shapeFragmentShaderPath, const char *skyboxVertexShaderPath, const char *skyboxFragmentShaderPath);

	public:
		static bool initMTGE(int majorOpenGLVersion, int minorOpenGLVersion, GLFWwindow **window, const char *windowTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const char *shapeVertexShaderPath, const char *shapeFragmentShaderPath, const char *skyboxVertexShaderPath, const char *skyboxFragmentShaderPath);
		static bool initMTGE(GLFWwindow **window, const char *windowTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const char *shapeVertexShaderPath, const char *shapeFragmentShaderPath, const char *skyboxVertexShaderPath, const char *skyboxFragmentShaderPath);
		static void freeResources();

		static Shader *getShapeShaderPtr();
		static Shader *getSkyboxShaderPtr();
	};
}