#pragma once

#include <vector>
#include <functional>

#include "Interaction/Player.h"
#include "CubeCharacterizer.h"
#include "Math/Vec.h"
#include "WorldMap.h"
#include "Rendering/Chunk.h"
#include "Rendering/Frustum.h"

namespace mtge {
	class WorldGenerator {
	private:
		enum class ChunkNeighborDirection {
			LEFT, RIGHT, FRONT, BACK
		};
		struct ChunkGenQueueMember {
			Chunk *baseChunk = nullptr;
			CubeCharacterizer *cubeCharacterizer;
			math::Vec2 position;
			math::Vec<int, 2> positionIndices;
			ChunkNeighborDirection direction;
		};
		Player *player = nullptr;
		std::function<float(float, float)> terrainFunc;
		std::vector<ChunkGenQueueMember> chunkGenQueue;
		unsigned int framesSinceLastNewChunk = 0;

		void setNeighborChunks(Chunk *addedChunk, bool testLeft, bool testRight, bool testFront, bool testBack);
		void generateChunksFromBase(CubeCharacterizer *cubeCharacterizer, Chunk *baseChunk);
		void generateChunksForBaseNeighbors(CubeCharacterizer *cubeCharacterizer, Chunk *baseChunk, unsigned int levels);

	public:
		WorldGenerator(Player *player, std::function<float(float, float)> terrainFunc);
		void generateChunks(CubeCharacterizer *cubeCharacterizer, unsigned int levels, bool frustumCull);
	};
}