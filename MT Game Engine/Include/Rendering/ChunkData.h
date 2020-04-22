#pragma once

#include <vector>

#include "Rendering/CubeData.h"
#include "Math/Vec.h"
#include "Texture/TextureAtlasSegment.h"

namespace mtge {
	class ChunkData {
	private:
		TextureAtlasSegment *texAtlasSegment;
		std::vector<float> vertexBuffer;

	public:
		ChunkData(TextureAtlasSegment *texAtlasSegment);
		void addCube(
			math::Vec3 offset,
			float scale,
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