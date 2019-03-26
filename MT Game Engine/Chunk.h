#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Shape.h"

namespace mtge {
	class Chunk {
	private:
		bool visible = true;

	protected:
		glm::vec3 position;

		void clearShapeVector();

	public:
		std::vector<Shape*> shapes = {};

		Chunk(glm::vec3 position);
		void newShape(Shape *shape);
		void deleteShape(unsigned int index);
		void setVisible(bool visible);
		void draw();
		int collision(glm::vec3 position, glm::vec3 dimensions);
		glm::vec3 getPosition();
		virtual void clearContents();
	};
}