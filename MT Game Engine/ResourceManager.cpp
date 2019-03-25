#include "ResourceManager.h"

namespace mtge {
	//Public
	bool ResourceManager::glfwStart(int majorOpenGLVersion, int minorOpenGLVersion, GLFWwindow **window, const char *windowTitle) {
		//GLFW Setup
		if (!glfwInit()) {
			std::cout << "ERROR: GLFW FAILED TO INITIALIZE" << std::endl;
			return 1;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorOpenGLVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorOpenGLVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//Window Setup
		*window = glfwCreateWindow(mtge::SCREEN_WIDTH, mtge::SCREEN_HEIGHT, windowTitle, NULL, NULL);
		if (!window) {
			std::cout << "ERROR: WINDOW FAILED TO INITIALIZE" << std::endl;
			glfwTerminate();
			return 1;
		}
		glfwMakeContextCurrent(*window);

		return 0;
	}
	bool ResourceManager::glewStart() {
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			std::cout << "ERROR: GLEW FAILED TO INITIALIZE" << std::endl;
			glfwTerminate();
			return 1;
		}
		return 0;
	}
	void ResourceManager::end() {
		glfwTerminate();
		mtge::Map::deleteAllChunks();
		mtge::Map::deleteSkybox();
	}
}