#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Shape.h"

namespace mtge {
	class Cube : public Shape {
	private:
		static const float VERTICES[];
		static const unsigned int VERTICES_SIZE = sizeof(float) * 288;
		Texture *textures[6];
		bool renderedSides[6];

	public:
		Cube(glm::vec3 pos, glm::vec3 dimensions, Shader *shader, Texture *textures[], bool renderedSides[]);
		Cube(glm::vec3 pos, glm::vec3 dimensions, Shader *shader, Texture *textures[]);
		bool collision(glm::vec3 position, glm::vec3 dimensions);
		void draw();
	};
}