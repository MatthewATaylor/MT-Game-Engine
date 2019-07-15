#include "RenderablesSet.h"

namespace mtge {
	//Public
	void RenderablesSet::setIsVisible(bool isVisible) {
		this->isVisible = isVisible;
	}
	bool RenderablesSet::getIsVisible() {
		return isVisible;
	}

	unsigned int RenderablesSet::getNumShapes() {
		return shapes.size();
	}
	Shape *RenderablesSet::getShapePtr(unsigned int index) {
		return shapes[index];
	}
	void RenderablesSet::appendShape(Shape *shape) {
		shapes.push_back(shape);
	}

	void RenderablesSet::eraseShape(unsigned int index) {
		delete shapes[index];
		shapes.erase(shapes.begin() + index);
	}
	void RenderablesSet::clearShapes() {
		for (unsigned int i = 0; i < shapes.size(); i++) {
			delete shapes[i];
		}
		shapes.clear();
	}

	void RenderablesSet::drawShape(unsigned int index) {
		if (isVisible) {
			shapes[index]->updateBuffers();
			shapes[index]->draw();
		}
	}
	void RenderablesSet::drawAllShapes() {
		if (isVisible) {
			for (unsigned int i = 0; i < shapes.size(); i++) {
				shapes[i]->updateBuffers();
				shapes[i]->draw();
			}
		}
	}

	bool RenderablesSet::checkSingleShapeCollision(unsigned int index, glm::vec3 position, glm::vec3 dimensions) {
		if (shapes[index]->collision(position, dimensions)) {
			return true;
		}
		return false;
	}
	int RenderablesSet::checkAllShapeCollisions(glm::vec3 position, glm::vec3 dimensions) {
		for (unsigned int i = 0; i < shapes.size(); i++) {
			if (shapes[i]->collision(position, dimensions)) {
				return i;
			}
		}
		return -1;
	}

	bool RenderablesSet::hasPosition() {
		return false;
	}
	glm::vec3 RenderablesSet::getPosition() {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
	void RenderablesSet::specifyRenderArea() {}

	//Destructor
	RenderablesSet::~RenderablesSet() {
		clearShapes();
	}
}