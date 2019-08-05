#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Shape.h"
#include "ResourceManager.h"

namespace mtge {
	class Cube : public Shape {
	private:
		static const float VERTICES[];
		static const unsigned int VERTICES_SIZE = sizeof(float) * 288;
		Texture *texture;
		bool renderedSides[6];

	public:
		Cube(glm::vec3 pos, glm::vec3 dimensions, Texture *texture);
		Cube(const Cube &cube);
		bool collision(glm::vec3 position, glm::vec3 dimensions);
		void draw();
		void setRenderedSides(bool renderedSides[6]);
	};
}