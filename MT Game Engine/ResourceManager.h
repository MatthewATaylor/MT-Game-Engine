#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GlobalConstants.h"
#include "Map.h"

namespace mtge {
	class ResourceManager {
	public:
		static bool glfwStart(int majorOpenGLVersion, int minorOpenGLVersion, GLFWwindow **window, const char *windowTitle);
		static bool glewStart();
		static void end();
	};
}