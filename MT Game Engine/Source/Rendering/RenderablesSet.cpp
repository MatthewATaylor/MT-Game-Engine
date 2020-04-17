#include "Rendering/RenderablesSet.h"

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
	void RenderablesSet::appendShape(Shape *shape, bool deletable) {
		if (deletable) {
			shape->setDeletable(true);
		}
		shapes.push_back(shape);
	}

	void RenderablesSet::eraseShape(unsigned int index) {
		if (shapes[index]->getDeletable()) {
			delete shapes[index];
		}
		shapes.erase(shapes.begin() + index);
	}
	void RenderablesSet::clearShapes() {
		for (unsigned int i = 0; i < shapes.size(); i++) {
			if (shapes[i]->getDeletable()) {
				delete shapes[i];
			}
		}
		shapes.clear();
	}

	void RenderablesSet::drawShape(unsigned int index) {
		if (isVisible) {
			//if (lastShapeType == ShapeType::UNDEFINED || lastShapeType != shapes[index]->getType()) {
				shapes[index]->updateBuffers();
				//lastShapeType = shapes[index]->getType();
			//}
			shapes[index]->draw();
		}
	}
	void RenderablesSet::drawAllShapes() {
		if (isVisible) {
			for (unsigned int i = 0; i < shapes.size(); i++) {
				//if (lastShapeType == ShapeType::UNDEFINED || lastShapeType != shapes[i]->getType()) {
					shapes[i]->updateBuffers();
					//lastShapeType = shapes[i]->getType();
				//}
				shapes[i]->draw();
			}
		}
	}

	bool RenderablesSet::checkSingleShapeCollision(unsigned int index, math::Vec<float, 3> position, math::Vec<float, 3> dimensions) {
		if (shapes[index]->collision(position, dimensions)) {
			return true;
		}
		return false;
	}
	int RenderablesSet::checkAllShapeCollisions(math::Vec<float, 3> position, math::Vec<float, 3> dimensions) {
		for (unsigned int i = 0; i < shapes.size(); i++) {
			if (shapes[i]->collision(position, dimensions)) {
				return i;
			}
		}
		return -1;
	}

	void RenderablesSet::setDeletable(bool deletable) {
		this->deletable = deletable;
	}
	bool RenderablesSet::getDeletable() const {
		return deletable;
	}

	bool RenderablesSet::hasPosition() {
		return false;
	}
	glm::vec3 RenderablesSet::getPosition() const {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
	void RenderablesSet::specifyRenderArea() {}

	//Destructor
	RenderablesSet::~RenderablesSet() {
		clearShapes();
	}
}