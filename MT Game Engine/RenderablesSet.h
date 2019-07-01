#pragma once

#include <vector>

#include "Shape.h"

namespace mtge {
	class RenderablesSet {
	private:
		bool isVisible = true;

	protected:
		std::vector<Shape*> shapes = {};

	public:
		void setIsVisible(bool isVisible);
		bool getIsVisible();

		unsigned int getNumShapes();
		Shape *getShapePtr(unsigned int index);
		void appendShape(Shape *shape);
		
		void eraseShape(unsigned int index);
		void clearShapes();

		void drawShape(unsigned int index);
		void drawAllShapes();

		bool checkSingleShapeCollision(unsigned int index, glm::vec3 position, glm::vec3 dimensions);
		int checkAllShapeCollisions(glm::vec3 position, glm::vec3 dimensions);

		virtual bool hasPosition();
		virtual glm::vec3 getPosition();
		virtual void specifyRenderArea();
	};
}