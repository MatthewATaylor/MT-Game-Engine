#pragma once

#include <vector>

#include "Rendering/Shape.h"
#include "Rendering/OldCube.h"
#include "Math/Vec.h"

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

		bool checkSingleShapeCollision(unsigned int index, math::Vec<float, 3> position, math::Vec<float, 3> dimensions);
		int checkAllShapeCollisions(math::Vec<float, 3> position, math::Vec<float, 3> dimensions);

		void setDeletable(bool deletable);
		bool getDeletable() const;

		virtual bool hasPosition();
		virtual glm::vec3 getPosition() const;
		virtual void specifyRenderArea();

		~RenderablesSet();
	};
}