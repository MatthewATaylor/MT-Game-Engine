#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Shape.h"

namespace mtge {
	class Chunk {
	private:
		glm::vec3 position;
		bool visible = true;

		void clearShapeVector();

	public:
		std::vector<Shape*> shapes = {};

		Chunk(glm::vec3 position);
		void newShape(Shape *shape);
		void deleteShape(unsigned int index);
		void setVisible(bool visible);
		void draw();
		int collision(glm::vec3 cameraPosition, const glm::vec3 DIMENSIONS);
		glm::vec3 getPosition();
		virtual void clearContents();
	};
}