#include "ResourceManager.h"

namespace mtge {
	Shader *ResourceManager::shapeShader = nullptr;
	Shader *ResourceManager::skyboxShader = nullptr;

	//Public
	bool ResourceManager::startGLFW(int majorOpenGLVersion, int minorOpenGLVersion) {
		//GLFW Setup
		if (!glfwInit()) {
			std::cout << "ERROR: GLFW FAILED TO INITIALIZE" << std::endl;
			return 1;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorOpenGLVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorOpenGLVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return 0;
	}
	bool ResourceManager::initWindow(GLFWwindow **window, const char *windowTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT) {
		*window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle, NULL, NULL);
		if (!window) {
			std::cout << "ERROR: WINDOW FAILED TO INITIALIZE" << std::endl;
			glfwTerminate();
			return 1;
		}
		glfwMakeContextCurrent(*window);

		return 0;
	}
	bool ResourceManager::startGLEW() {
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			std::cout << "ERROR: GLEW FAILED TO INITIALIZE" << std::endl;
			glfwTerminate();
			return 1;
		}
		return 0;
	}
	void ResourceManager::initMTGE(const char *shapeVertexShaderPath, const char *shapeFragmentShaderPath, const char *skyboxVertexShaderPath, const char *skyboxFragmentShaderPath) {
		shapeShader = new Shader(shapeVertexShaderPath, shapeFragmentShaderPath);
		skyboxShader = new Shader(skyboxVertexShaderPath, skyboxFragmentShaderPath);
	}
	void ResourceManager::freeResources() {
		delete shapeShader;
		delete skyboxShader;
	}
}