#pragma once

#include "Interaction/Player.h"
#include "Rendering/Texture/TextureAtlasSegment.h"
#include "Math/Vec.h"
#include "WorldMap.h"
#include "Rendering/Chunk.h"

namespace mtge {
	class WorldGenerator {
	private:
		Player *player = nullptr;

		void setNeighborChunks(Chunk *addedChunk, bool testLeft, bool testRight, bool testFront, bool testBack);
		void generateChunksFromBase(TextureAtlasSegment *texAtlasSegment, Chunk *baseChunk);

	public:
		WorldGenerator(Player *player);
		void generateChunks(TextureAtlasSegment *texAtlasSegment);
	};
}