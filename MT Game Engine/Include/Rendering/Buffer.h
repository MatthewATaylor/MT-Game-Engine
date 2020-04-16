#pragma once

#include <GL/glew.h>

#include "Interaction/Input.h"
#include "Window.h"

namespace mtge {
	class Buffer {
	private:
		const float *VERTICES = nullptr;
		const unsigned int VERTICES_SIZE;
		unsigned int vertexArrayID, vertexBufferID;
		const bool POSITION_ONLY;
		unsigned int dataBreadth;
		bool buffersUpdated = false;

		static Window *window;

	public:
		Buffer(const float *VERTICES, const unsigned int VERTICES_SIZE, const bool POSITION_ONLY);
		void useBuffer();
		void updateBuffer();
		void deleteBuffer();

		static void setWindow(Window *window);
	};
}