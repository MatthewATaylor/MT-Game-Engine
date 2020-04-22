#include "WorldGenerator.h"

namespace mtge {
	//Constructor
	WorldGenerator::WorldGenerator(Player *player) {
		this->player = player;
	}

	//Private
	void WorldGenerator::setNeighborChunks(Chunk *addedChunk, bool testLeft, bool testRight, bool testFront, bool testBack) {
		math::Vec<int, 2> addedChunkIndices = addedChunk->getPositionIndices();
		for (unsigned int i = 0; i < WorldMap::getNumChunks(); i++) {
			Chunk *testChunk = WorldMap::getChunkPtr(i);

			if (testLeft) {
				if (testChunk->getPositionIndices().getX() == addedChunkIndices.getX() - 1 &&
					testChunk->getPositionIndices().getY() == addedChunkIndices.getY()) {

					addedChunk->setLeftNeighbor(testChunk);
				}
			}

			if (testRight) {
				if (testChunk->getPositionIndices().getX() == addedChunkIndices.getX() + 1 &&
					testChunk->getPositionIndices().getY() == addedChunkIndices.getY()) {

					addedChunk->setRightNeighbor(testChunk);
				}
			}

			if (testFront) {
				if (testChunk->getPositionIndices().getX() == addedChunkIndices.getX() &&
					testChunk->getPositionIndices().getY() == addedChunkIndices.getY() + 1) {

					addedChunk->setFrontNeighbor(testChunk);
				}
			}

			if (testBack) {
				if (testChunk->getPositionIndices().getX() == addedChunkIndices.getX() &&
					testChunk->getPositionIndices().getY() == addedChunkIndices.getY() - 1) {

					addedChunk->setBackNeighbor(testChunk);
				}
			}
		}
	}

	//Public
	void WorldGenerator::generateChunks(TextureAtlasSegment *texAtlasSegment) {
		Chunk *currentChunk = WorldMap::getChunkPtr(player->getChunkIndex());
		math::Vec2 chunkPosition = currentChunk->getPosition();
		if (!currentChunk->leftNeighbor) {
			Chunk *addedChunk = new Chunk(texAtlasSegment, math::Vec2(chunkPosition.getX() - Chunk::CHUNK_SIZE, chunkPosition.getY()));
			currentChunk->setLeftNeighbor(addedChunk);
			WorldMap::addChunk(addedChunk);
			//setNeighborChunks(addedChunk, true, false, true, true);
			setNeighborChunks(addedChunk, true, true, true, true);
		}
		if (!currentChunk->rightNeighbor) {
			Chunk *addedChunk = new Chunk(texAtlasSegment, math::Vec2(chunkPosition.getX() + Chunk::CHUNK_SIZE, chunkPosition.getY()));
			currentChunk->setRightNeighbor(addedChunk);
			WorldMap::addChunk(addedChunk);
			//setNeighborChunks(addedChunk, false, true, true, true);
			setNeighborChunks(addedChunk, true, true, true, true);
		}
		if (!currentChunk->frontNeighbor) {
			Chunk *addedChunk = new Chunk(texAtlasSegment, math::Vec2(chunkPosition.getX(), chunkPosition.getY() + Chunk::CHUNK_SIZE));
			currentChunk->setFrontNeighbor(addedChunk);
			WorldMap::addChunk(addedChunk);
			//setNeighborChunks(addedChunk, true, true, true, false);
			setNeighborChunks(addedChunk, true, true, true, true);
		}
		if (!currentChunk->backNeighbor) {
			Chunk *addedChunk = new Chunk(texAtlasSegment, math::Vec2(chunkPosition.getX(), chunkPosition.getY() - Chunk::CHUNK_SIZE));
			currentChunk->setBackNeighbor(addedChunk);
			WorldMap::addChunk(addedChunk);
			//setNeighborChunks(addedChunk, true, true, false, true);
			setNeighborChunks(addedChunk, true, true, true, true);
		}
	}
}