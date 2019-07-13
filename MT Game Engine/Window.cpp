#include "Window.h"

namespace mtge {
	//Constructor
	Window::Window(const char *windowTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, bool resizable) {
		if (!resizable) {
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		}

		window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle, 0, 0);
		if (!window) {
			std::cout << "ERROR [FUNCTION: Window]: WINDOW FAILED TO INITIALIZE" << std::endl << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);

		if (resizable) {
			glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_SCISSOR_TEST);
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		glScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	//Public
	void Window::frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	}
	void Window::setShouldClose(bool shouldClose) {
		glfwSetWindowShouldClose(window, shouldClose);
	}
	bool Window::getShouldClose() {
		return glfwWindowShouldClose(window);
	}
	GLFWwindow *Window::getPtr_GLFW() {
		return window;
	}
}