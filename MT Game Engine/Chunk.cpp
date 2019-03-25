#include "Chunk.h"

namespace mtge {
	//Constructor
	Chunk::Chunk(glm::vec3 position) {
		this->position = position;
	}

	//Private
	void Chunk::clearShapeVector() {
		for (unsigned int i = 0; i < shapes.size(); i++) {
			delete shapes[i];
		}
		shapes.clear();
	}

	//Public
	void Chunk::newShape(Shape *shape) {
		shapes.push_back(shape);
	}
	void Chunk::deleteShape(unsigned int index) {
		delete shapes[index];
		shapes.erase(shapes.begin() + index);
	}
	void Chunk::setVisible(bool visible) {
		this->visible = visible;
	}
	void Chunk::draw() {
		if (visible) {
			const char *prevShapeName = "";
			for (unsigned int i = 0; i < shapes.size(); i++) {
				const char *shapeName = shapes[i]->getName();
				if (strcmp(shapeName, prevShapeName) != 0) {
					shapes[i]->updateBuffers();
				}
				shapes[i]->draw();
				prevShapeName = shapeName;
			}
		}
	}
	int Chunk::collision(glm::vec3 cameraPosition, const glm::vec3 DIMENSIONS) {
		if (visible) {
			for (unsigned int i = 0; i < shapes.size(); i++) {
				if (shapes[i]->collision(cameraPosition, DIMENSIONS)) {
					return i;
				}
			}
		}
		return -1;
	}
	glm::vec3 Chunk::getPosition() {
		return position;
	}
	void Chunk::clearContents() {
		clearShapeVector();
	}
}