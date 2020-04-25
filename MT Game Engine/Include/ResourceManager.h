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

	public:
		static bool startGLFW();
		static bool startGLFW(int majorOpenGLVersion, int minorOpenGLVersion);
		static bool startGLEW();
		static void startOpenGL();
		static void freeResources();
	};
}