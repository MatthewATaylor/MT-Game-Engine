#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../Texture.h"
#include "Shape.h"
#include "../ResourceManager.h"
#include "../TextureAtlasSegment.h"

namespace mtge {
	class Cube : public Shape {
	private:
		static const unsigned int NUM_VERTICES = 288;
		static const unsigned int VERTICES_SIZE = sizeof(float) * NUM_VERTICES;

		Texture *textureAtlas = nullptr;
		const TextureAtlasSegment *texAS;

		const float VERTICES[NUM_VERTICES] = {
			//Positions-----------Colors---------------Texture----------------------------------------------------------------------------------------
			//Triangle 1, Front
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(2, CoordBuffer_T::TOP   ),  //Top Left
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(1, CoordBuffer_T::BOTTOM),  //Bottom Left
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(1, CoordBuffer_T::BOTTOM),  //Bottom Right
			//Triangle 2, Front
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(2, CoordBuffer_T::TOP   ),  //Top Left
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(1, CoordBuffer_T::BOTTOM),  //Bottom Right
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(2, CoordBuffer_T::TOP   ),  //Top Right

			//Triangle 1, Back
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(4, CoordBuffer_T::TOP   ),  //Top Right
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(3, CoordBuffer_T::BOTTOM),  //Bottom Left
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(3, CoordBuffer_T::BOTTOM),  //Bottom Right
			//Triangle 2, Back
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(4, CoordBuffer_T::TOP   ),  //Top Right
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(4, CoordBuffer_T::TOP   ),  //Top Left
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(3, CoordBuffer_T::BOTTOM),  //Bottom Left

			//Triangle 1, Left
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(0, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(3, CoordBuffer_T::TOP   ),  //Top Left
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(0, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(2, CoordBuffer_T::BOTTOM),  //Bottom Left
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(2, CoordBuffer_T::BOTTOM),  //Bottom Right
			//Triangle 2, Left
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(0, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(3, CoordBuffer_T::TOP   ),  //Top Left
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(2, CoordBuffer_T::BOTTOM),  //Bottom Right
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(3, CoordBuffer_T::TOP   ),  //Top Right

			//Triangle 1, Right
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(3, CoordBuffer_T::TOP   ),  //Top Left
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(2, CoordBuffer_T::BOTTOM),  //Bottom Left
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(3, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(2, CoordBuffer_T::BOTTOM),  //Bottom Right
			//Triangle 2, Right
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(3, CoordBuffer_T::TOP   ),  //Top Left
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(3, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(2, CoordBuffer_T::BOTTOM),  //Bottom Right
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(3, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(3, CoordBuffer_T::TOP   ),  //Top Right

			//Triangle 1, Top
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(1, CoordBuffer_T::TOP   ),  //Top Left
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(0, CoordBuffer_T::BOTTOM),  //Bottom Left
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(0, CoordBuffer_T::BOTTOM),  //Bottom Right
			//Triangle 2, Top
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(1, CoordBuffer_T::TOP   ),  //Top Left
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(0, CoordBuffer_T::BOTTOM),  //Bottom Right
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(1, CoordBuffer_T::TOP   ),  //Top Right

			//Triangle 1, Bottom
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(2, CoordBuffer_T::BOTTOM),  //Bottom Left
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(3, CoordBuffer_T::TOP   ),  //Top Right
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(3, CoordBuffer_T::TOP   ),  //Top Left
			//Triangle 2, Bottom
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(1, CoordBuffer_S::LEFT ),  texAS->getTexCoord_T(2, CoordBuffer_T::BOTTOM),  //Bottom Left
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(2, CoordBuffer_T::BOTTOM),  //Bottom Right
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  texAS->getTexCoord_S(2, CoordBuffer_S::RIGHT),  texAS->getTexCoord_T(3, CoordBuffer_T::TOP   ),  //Top Right
		};

	public:
		Cube(glm::vec3 pos, glm::vec3 dimensions, Texture *textureAtlas, TextureAtlasSegment *textureAtlasSegment);
		Cube(const Cube &cube);
		bool collision(glm::vec3 position, glm::vec3 dimensions);
		void draw();
	};
}