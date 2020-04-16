#include "Rendering/Buffer.h"

namespace mtge {
	Window *Buffer::window = nullptr;

	//Constructor
	Buffer::Buffer(const float *VERTICES, const unsigned int VERTICES_SIZE, const bool POSITION_ONLY) : VERTICES_SIZE(VERTICES_SIZE), POSITION_ONLY(POSITION_ONLY) {
		this->VERTICES = VERTICES;
		this->dataBreadth = dataBreadth;
	}

	//Public
	void Buffer::useBuffer() {
		//Set Vertex Array/Buffer IDs
		glGenVertexArrays(1, &vertexArrayID);
		glGenBuffers(1, &vertexBufferID);

		//Bind Vertex Array/Buffers to Use
		glBindVertexArray(vertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, VERTICES_SIZE, VERTICES, GL_STATIC_DRAW);

		if (POSITION_ONLY) {
			//Setup Vertex Attribute (for Positions)
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
		}
		else {
			//Setup Vertex Attribute (for Positions)
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			//Setup Vertex Attribute (for Colors)
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);

			//Setup Vertex Attributes (for Texture)
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
		}
	}
	void Buffer::updateBuffer() {
		glBindVertexArray(vertexArrayID);
		if (!buffersUpdated) {
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, VERTICES_SIZE, VERTICES, GL_STATIC_DRAW);
			buffersUpdated = true;
		}
	}
	void Buffer::deleteBuffer() {
		glDeleteVertexArrays(1, &vertexArrayID);
		glDeleteBuffers(1, &vertexBufferID);
	}
	void Buffer::setWindow(Window *window) {
		Buffer::window = window;
	}
}