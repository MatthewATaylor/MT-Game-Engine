#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Shape.h"
#include "ResourceManager.h"

namespace mtge {
	class Cube : public Shape {
	private:
		static const unsigned int NUM_VERTICES = 288;
		static const unsigned int VERTICES_SIZE = sizeof(float) * NUM_VERTICES;
		const float TEXTURE_S_OFFSET;
		const float TEXTURE_T_OFFSET;
		const float VERTICES[NUM_VERTICES] = {
			//Positions-----------Colors---------------Texture---------------------------------------------
			//Triangle 1, Front
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  0.50f + TEXTURE_T_OFFSET,  //Top Left
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  0.25f + TEXTURE_T_OFFSET,  //Bottom Left
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  0.25f + TEXTURE_T_OFFSET,  //Bottom Right
			//Triangle 2, Front
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  0.50f + TEXTURE_T_OFFSET,  //Top Left
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  0.25f + TEXTURE_T_OFFSET,  //Bottom Right
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  0.50f + TEXTURE_T_OFFSET,  //Top Right

			//Triangle 1, Back
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  1.00f + TEXTURE_T_OFFSET,  //Top Right
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  0.75f + TEXTURE_T_OFFSET,  //Bottom Left
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  0.75f + TEXTURE_T_OFFSET,  //Bottom Right
			//Triangle 2, Back
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  1.00f + TEXTURE_T_OFFSET,  //Top Right
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  1.00f + TEXTURE_T_OFFSET,  //Top Left
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  0.75f + TEXTURE_T_OFFSET,  //Bottom Left

			//Triangle 1, Left
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.00f + TEXTURE_S_OFFSET,  0.75f + TEXTURE_T_OFFSET,  //Top Left
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.00f + TEXTURE_S_OFFSET,  0.50f + TEXTURE_T_OFFSET,  //Bottom Left
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  0.50f + TEXTURE_T_OFFSET,  //Bottom Right
			//Triangle 2, Left
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.00f + TEXTURE_S_OFFSET,  0.75f + TEXTURE_T_OFFSET,  //Top Left
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  0.50f + TEXTURE_T_OFFSET,  //Bottom Right
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  0.75f + TEXTURE_T_OFFSET,  //Top Right

			//Triangle 1, Right
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  0.75f + TEXTURE_T_OFFSET,  //Top Left
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  0.50f + TEXTURE_T_OFFSET,  //Bottom Left
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.75f + TEXTURE_S_OFFSET,  0.50f + TEXTURE_T_OFFSET,  //Bottom Right
			//Triangle 2, Right
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  0.75f + TEXTURE_T_OFFSET,  //Top Left
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.75f + TEXTURE_S_OFFSET,  0.50f + TEXTURE_T_OFFSET,  //Bottom Right
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.75f + TEXTURE_S_OFFSET,  0.75f + TEXTURE_T_OFFSET,  //Top Right

			//Triangle 1, Top
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  0.25f + TEXTURE_T_OFFSET,  //Top Left
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  0.00f + TEXTURE_T_OFFSET,  //Bottom Left
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  0.00f + TEXTURE_T_OFFSET,  //Bottom Right
			//Triangle 2, Top
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  0.25f + TEXTURE_T_OFFSET,  //Top Left
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  0.00f + TEXTURE_T_OFFSET,  //Bottom Right
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  0.25f + TEXTURE_T_OFFSET,  //Top Right

			//Triangle 1, Bottom
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  0.50f + TEXTURE_T_OFFSET,  //Bottom Left
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  0.75f + TEXTURE_T_OFFSET,  //Top Right
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  0.75f + TEXTURE_T_OFFSET,  //Top Left
			//Triangle 2, Bottom
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.25f + TEXTURE_S_OFFSET,  0.50f + TEXTURE_T_OFFSET,  //Bottom Left
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  0.50f + TEXTURE_T_OFFSET,  //Bottom Right
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f + TEXTURE_S_OFFSET,  0.75f + TEXTURE_T_OFFSET,  //Top Right
		};
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