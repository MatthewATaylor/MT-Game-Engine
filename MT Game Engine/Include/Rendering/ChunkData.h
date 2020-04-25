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
		std::vector<float> waterQueue;

	public:
		void addSolidCube(
			CubeTexture *cubeTexture,
			math::Vec3 offset,
			float scale,
			bool hasTopNeighbor,
			bool hasBottomNeighbor,
			bool hasLeftNeighbor,
			bool hasRightNeighbor,
			bool hasFrontNeighbor,
			bool hasBackNeighbor
		);
		void addWaterToQueue(
			CubeTexture *cubeTexture,
			math::Vec3 offset,
			float scale,
			bool hasTopNeighbor
		);
		void addTransparentCubesToBuffer();
		int getVerticesInBuffer();
		void sendBuffer();
	};
}