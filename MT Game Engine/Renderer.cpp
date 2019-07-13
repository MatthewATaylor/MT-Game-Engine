#include "Renderer.h"

namespace mtge {
	//Public
	void Renderer::clear(int clearColor_R, int clearColor_G, int clearColor_B) {
		const int MAX_COLOR_VALUE = 255;
		glClearColor(float(clearColor_R) / float(MAX_COLOR_VALUE), float(clearColor_G) / float(MAX_COLOR_VALUE), float(clearColor_B) / float(MAX_COLOR_VALUE), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Renderer::applyDrawCalls(Window *window) {
		glfwSwapBuffers(window->getPtr_GLFW());
	}
}