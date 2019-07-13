#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

namespace mtge {
	class Renderer {
	public:
		static void clear(int clearColor_R, int clearColor_G, int clearColor_B);
		static void applyDrawCalls(Window *window);
	};
}