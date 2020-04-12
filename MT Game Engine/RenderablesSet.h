#pragma once

#include <vector>

#include "Shape.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Triangle.h"

namespace mtge {
	class RenderablesSet {
	private:
		ShapeType lastShapeType = ShapeType::UNDEFINED;
		bool isVisible = true;
		bool deletable = false;
		std::vector<Shape*> shapes = {};

	public:
		void setIsVisible(bool isVisible);
		bool getIsVisible();

		unsigned int getNumShapes();
		Shape *getShapePtr(unsigned int index);
		void appendShape(Shape *shape);
		void appendShape(Shape *shape, bool deletable);
		
		void eraseShape(unsigned int index);
		void clearShapes();

		void drawShape(unsigned int index);
		void drawAllShapes();

		bool checkSingleShapeCollision(unsigned int index, glm::vec3 position, glm::vec3 dimensions);
		int checkAllShapeCollisions(glm::vec3 position, glm::vec3 dimensions);

		void setDeletable(bool deletable);
		bool getDeletable() const;

		virtual bool hasPosition();
		virtual glm::vec3 getPosition() const;
		virtual void specifyRenderArea();

		~RenderablesSet();
	};
}