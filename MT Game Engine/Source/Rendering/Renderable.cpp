#include "Rendering/Renderable.h"

namespace mtge {
	//Constructor
	Renderable::Renderable() {
		glGenVertexArrays(1, &vertexArrayID);
		glGenBuffers(1, &vertexBufferID);
	}

	//Destructor
	Renderable::~Renderable() {
		glDeleteVertexArrays(1, &vertexArrayID);
		glDeleteBuffers(1, &vertexBufferID);
	}
}