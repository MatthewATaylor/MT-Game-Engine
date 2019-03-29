#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Map.h"

namespace mtge {
	class ResourceManager {
	public:
		static bool startGLFW(int majorOpenGLVersion, int minorOpenGLVersion);
		static bool initWindow(GLFWwindow **window, const char *windowTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
		static bool startGLEW();
	};
}