#pragma once

#include <vector>
#include <iostream>

#include "Rendering/CubeData.h"
#include "Math/Vec.h"
#include "Texture/CubeTexture.h"

namespace mtge {
	class ChunkData {
	private:
		std::vector<float> vertexBuffer;

	public:
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
	};
}