#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderable/Cube.h"
#include "Renderable/CubeData.h"
#include "Math/Vec.h"
#include "Math/Mat.h"
#include "ResourceManager.h"

namespace mtge {
	class Chunk {
	private:
		static const unsigned int LENGTH_IN_CUBES = 16;
		static const unsigned int NUM_CUBES = LENGTH_IN_CUBES * LENGTH_IN_CUBES * LENGTH_IN_CUBES;
		Cube ****cubes = nullptr; //(i, j, k) = (x, y, z)    +i -> further right    +j -> higher up    +k -> further forwards
		unsigned int vertexArrayID;
		unsigned int vertexBufferID;

		bool cubeHasTopNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasBottomNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasLeftNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasRightNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasFrontNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasBackNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);

	public:
		Chunk();
		~Chunk();
		void genBuffer();
		void render(glm::mat4 projectionMatrix, math::Mat<float, 4, 4> viewMatrix);
	};
}