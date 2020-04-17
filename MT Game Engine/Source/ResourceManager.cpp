#include "ResourceManager.h"

namespace mtge {
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
	void ResourceManager::freeResources() {
		glfwTerminate();
	}
}