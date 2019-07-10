#include "ResourceManager.h"

namespace mtge {
	Shader *ResourceManager::shapeShader = nullptr;
	Shader *ResourceManager::skyboxShader = nullptr;

	//Private
	bool ResourceManager::startGLFW(int majorOpenGLVersion, int minorOpenGLVersion) {
		//GLFW Setup
		if (!glfwInit()) {
			std::cout << "ERROR [FUNCTION: startGLFW]: GLFW FAILED TO INITIALIZE" << std::endl << std::endl;
			return 1;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorOpenGLVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorOpenGLVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return 0;
	}
	bool ResourceManager::initWindow(GLFWwindow **window, const char *windowTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT) {
		*window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle, 0, 0);
		if (!window) {
			std::cout << "ERROR [FUNCTION: initWindow]: WINDOW FAILED TO INITIALIZE" << std::endl << std::endl;
			glfwTerminate();
			return 1;
		}
		glfwMakeContextCurrent(*window);

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
	void ResourceManager::loadShaders(const char *shapeVertexShaderPath, const char *shapeFragmentShaderPath, const char *skyboxVertexShaderPath, const char *skyboxFragmentShaderPath) {
		shapeShader = new Shader(shapeVertexShaderPath, shapeFragmentShaderPath);
		skyboxShader = new Shader(skyboxVertexShaderPath, skyboxFragmentShaderPath);
	}

	//Public

	bool ResourceManager::initMTGE(int majorOpenGLVersion, int minorOpenGLVersion, GLFWwindow **window, const char *windowTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const char *shapeVertexShaderPath, const char *shapeFragmentShaderPath, const char *skyboxVertexShaderPath, const char *skyboxFragmentShaderPath) {
		if (startGLFW(majorOpenGLVersion, minorOpenGLVersion)) {
			return 1;
		}
		if (initWindow(window, windowTitle, SCREEN_WIDTH, SCREEN_HEIGHT)) {
			return 1;
		}
		if (startGLEW()) {
			return 1;
		}
		loadShaders(shapeVertexShaderPath, shapeFragmentShaderPath, skyboxVertexShaderPath, skyboxFragmentShaderPath);
		return 0;
	}

	bool ResourceManager::initMTGE(GLFWwindow **window, const char *windowTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const char *shapeVertexShaderPath, const char *shapeFragmentShaderPath, const char *skyboxVertexShaderPath, const char *skyboxFragmentShaderPath) {
		if (startGLFW(DEFAULT_MAJOR_GL, DEFAULT_MINOR_GL)) {
			return 1;
		}
		if (initWindow(window, windowTitle, SCREEN_WIDTH, SCREEN_HEIGHT)) {
			return 1;
		}
		if (startGLEW()) {
			return 1;
		}
		loadShaders(shapeVertexShaderPath, shapeFragmentShaderPath, skyboxVertexShaderPath, skyboxFragmentShaderPath);
		return 0;
	}
	void ResourceManager::freeResources() {
		delete shapeShader;
		delete skyboxShader;
	}
	Shader *ResourceManager::getShapeShaderPtr() {
		return shapeShader;
	}
	Shader *ResourceManager::getSkyboxShaderPtr() {
		return skyboxShader;
	}
}