#pragma once

#include <vector>

#include "Interaction/Player.h"
#include "Rendering/Texture/TextureAtlasSegment.h"
#include "Math/Vec.h"
#include "WorldMap.h"
#include "Rendering/Chunk.h"

namespace mtge {
	class WorldGenerator {
	private:
		enum class ChunkNeighborDirection {
			LEFT, RIGHT, FRONT, BACK
		};
		struct ChunkGenQueueMember {
			Chunk *baseChunk = nullptr;
			math::Vec2 newChunkPosition;
			ChunkNeighborDirection direction;
		};
		Player *player = nullptr;
		std::vector<ChunkGenQueueMember> chunkGenQueue;

		void setNeighborChunks(Chunk *addedChunk, bool testLeft, bool testRight, bool testFront, bool testBack);
		void generateChunksFromBase(TextureAtlasSegment *texAtlasSegment, Chunk *baseChunk);

	public:
		WorldGenerator(Player *player);
		void generateChunks(TextureAtlasSegment *texAtlasSegment);
	};
}