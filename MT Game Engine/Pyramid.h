#pragma once

#include "Shape.h"
#include "Texture.h"

namespace mtge {
	class Pyramid : public Shape {
	private:
		static const float VERTICES[];
		static const unsigned int VERTICES_SIZE = sizeof(float) * 108;
		Texture *textures[4];

	public:
		Pyramid(glm::vec3 pos, glm::vec3 dimensions, Shader *shader, Texture *texture[]);
		void draw();
	};
}