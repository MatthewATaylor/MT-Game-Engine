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
	void WorldGenerator::generateChunksFromBase(TextureAtlasSegment *texAtlasSegment, Chunk *baseChunk) {
		math::Vec2 chunkPosition = baseChunk->getPosition();
		if (!baseChunk->leftNeighbor) {
			Chunk *addedChunk = new Chunk(texAtlasSegment, math::Vec2(chunkPosition.getX() - Chunk::CHUNK_SIZE, chunkPosition.getY()));
			baseChunk->setLeftNeighbor(addedChunk);
			WorldMap::addChunk(addedChunk);
			setNeighborChunks(addedChunk, true, false, true, true);
		}
		if (!baseChunk->rightNeighbor) {
			Chunk *addedChunk = new Chunk(texAtlasSegment, math::Vec2(chunkPosition.getX() + Chunk::CHUNK_SIZE, chunkPosition.getY()));
			baseChunk->setRightNeighbor(addedChunk);
			WorldMap::addChunk(addedChunk);
			setNeighborChunks(addedChunk, false, true, true, true);
		}
		if (!baseChunk->frontNeighbor) {
			Chunk *addedChunk = new Chunk(texAtlasSegment, math::Vec2(chunkPosition.getX(), chunkPosition.getY() + Chunk::CHUNK_SIZE));
			baseChunk->setFrontNeighbor(addedChunk);
			WorldMap::addChunk(addedChunk);
			setNeighborChunks(addedChunk, true, true, true, false);
		}
		if (!baseChunk->backNeighbor) {
			Chunk *addedChunk = new Chunk(texAtlasSegment, math::Vec2(chunkPosition.getX(), chunkPosition.getY() - Chunk::CHUNK_SIZE));
			baseChunk->setBackNeighbor(addedChunk);
			WorldMap::addChunk(addedChunk);
			setNeighborChunks(addedChunk, true, true, false, true);
		}
	}

	//Public
	void WorldGenerator::generateChunks(TextureAtlasSegment *texAtlasSegment) {
		Chunk *currentChunk = WorldMap::getChunkPtr(player->getChunkIndex());
		
		generateChunksFromBase(texAtlasSegment, currentChunk);

		generateChunksFromBase(texAtlasSegment, currentChunk->leftNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->rightNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->frontNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->backNeighbor);

		generateChunksFromBase(texAtlasSegment, currentChunk->leftNeighbor->leftNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->leftNeighbor->rightNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->leftNeighbor->frontNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->leftNeighbor->backNeighbor);

		generateChunksFromBase(texAtlasSegment, currentChunk->rightNeighbor->leftNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->rightNeighbor->rightNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->rightNeighbor->frontNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->rightNeighbor->backNeighbor);

		generateChunksFromBase(texAtlasSegment, currentChunk->frontNeighbor->leftNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->frontNeighbor->rightNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->frontNeighbor->frontNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->frontNeighbor->backNeighbor);

		generateChunksFromBase(texAtlasSegment, currentChunk->backNeighbor->leftNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->backNeighbor->rightNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->backNeighbor->frontNeighbor);
		generateChunksFromBase(texAtlasSegment, currentChunk->backNeighbor->backNeighbor);
	}
}