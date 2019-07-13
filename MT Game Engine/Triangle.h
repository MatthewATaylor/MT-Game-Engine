#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Shape.h"
#include "ResourceManager.h"

namespace mtge {
	class Triangle : public Shape {
	private:
		static const float VERTICES[];
		static const unsigned int VERTICES_SIZE = sizeof(float) * 24;
		Texture *texture;

	public:
		Triangle(glm::vec3 pos, glm::vec3 dimensions, Texture *texture);
		void draw();
	};
}