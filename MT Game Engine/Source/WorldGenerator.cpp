#include "WorldGenerator.h"

namespace mtge {
	//Constructor
	WorldGenerator::WorldGenerator(Player *player) {
		this->player = player;
	}

	//Public
	void WorldGenerator::generateChunks(TextureAtlasSegment *texAtlasSegment) {
		Chunk *currentChunk = WorldMap::getChunkPtr(player->getChunkIndex());
		math::Vec2 chunkPosition = currentChunk->getPosition();
		if (!currentChunk->backNeighbor) {
			Chunk *backChunk = new Chunk(texAtlasSegment, math::Vec2(chunkPosition.getX(), chunkPosition.getY() - Chunk::CHUNK_SIZE));
			currentChunk->setBackNeighbor(backChunk);
			WorldMap::addChunk(backChunk);
		}
	}
}