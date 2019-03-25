#pragma once

#include <GL/glew.h>

namespace mtge {
	class Buffer {
	private:
		const float *VERTICES = nullptr;
		const unsigned int VERTICES_SIZE;
		unsigned int vertexArrayID, vertexBufferID;
		const bool POSITION_ONLY;
		unsigned int dataBreadth;

	public:
		Buffer(const float *VERTICES, const unsigned int VERTICES_SIZE, const bool POSITION_ONLY);
		void useBuffer();
		void updateBuffer();
		void deleteBuffer();
	};
}