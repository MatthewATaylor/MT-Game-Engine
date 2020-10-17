#pragma once

#include <cmath>

#include "Rendering/CubeData.h"
#include "Math/Vec.h"
#include "Texture/CubeTexture.h"

namespace mtge {
	class ChunkData {
	private:
		static const unsigned int LENGTH_IN_CUBES = 12;
		static const unsigned int NUM_FACES = LENGTH_IN_CUBES * LENGTH_IN_CUBES * LENGTH_IN_CUBES * 6;
		static const unsigned int MAX_VERTEX_BUFFER_SIZE = NUM_FACES * CubeData::FACE_VERTEX_BUFFER_LENGTH;

		unsigned int vertexBufferLength = 0;
		float *vertexBuffer = nullptr;

	public:
		ChunkData();
		void addCube(
			CubeTexture *cubeTexture,
			math::Vec<unsigned int, 3> indices,
			bool hasTopNeighbor,
			bool hasBottomNeighbor,
			bool hasLeftNeighbor,
			bool hasRightNeighbor,
			bool hasFrontNeighbor,
			bool hasBackNeighbor
		);
		int getVerticesInBuffer();
		void sendBuffer();
		~ChunkData();
	};
}