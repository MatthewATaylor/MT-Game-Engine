#include "Chunk.h"

namespace mtge {
	//Constructor
	Chunk::Chunk(glm::vec3 position) {
		this->position = position;
	}

	//Protected
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
			ShapeType prevShapeType = ShapeType::UNDEFINED;
			for (unsigned int i = 0; i < shapes.size(); i++) {
				ShapeType shapeType = shapes[i]->getType();
				if (shapeType != prevShapeType) {
					shapes[i]->updateBuffers();
				}
				shapes[i]->draw();
				prevShapeType = shapeType;
			}
		}
	}
	int Chunk::collision(glm::vec3 position, glm::vec3 dimensions) {
		if (visible) {
			for (unsigned int i = 0; i < shapes.size(); i++) {
				if (shapes[i]->collision(position, dimensions)) {
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
	void Chunk::setRenderArea() {}
}