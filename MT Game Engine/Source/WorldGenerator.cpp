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
		math::Vec<int, 2> baseChunkPositionIndices = baseChunk->getPositionIndices();
		math::Vec<int, 2> leftChunkPositionIndices = math::Vec<int, 2>(baseChunkPositionIndices.getX() - 1, baseChunkPositionIndices.getY());
		math::Vec<int, 2> rightChunkPositionIndices = math::Vec<int, 2>(baseChunkPositionIndices.getX() + 1, baseChunkPositionIndices.getY());
		math::Vec<int, 2> frontChunkPositionIndices = math::Vec<int, 2>(baseChunkPositionIndices.getX(), baseChunkPositionIndices.getY() + 1);
		math::Vec<int, 2> backChunkPositionIndices = math::Vec<int, 2>(baseChunkPositionIndices.getX(), baseChunkPositionIndices.getY() - 1);

		math::Vec2 leftChunkPosition(baseChunk->getPosition().getX() - Chunk::CHUNK_SIZE, baseChunk->getPosition().getY());
		math::Vec2 rightChunkPosition(baseChunk->getPosition().getX() + Chunk::CHUNK_SIZE, baseChunk->getPosition().getY());
		math::Vec2 frontChunkPosition(baseChunk->getPosition().getX(), baseChunk->getPosition().getY() + Chunk::CHUNK_SIZE);
		math::Vec2 backChunkPosition(baseChunk->getPosition().getX(), baseChunk->getPosition().getY() - Chunk::CHUNK_SIZE);

		bool leftChunkInQueue = false;
		bool rightChunkInQueue = false;
		bool frontChunkInQueue = false;
		bool backChunkInQueue = false;

		for (unsigned int i = 0; i < chunkGenQueue.size(); i++) {
			if (chunkGenQueue[i].positionIndices == leftChunkPositionIndices) {
				leftChunkInQueue = true;
			}
			if (chunkGenQueue[i].positionIndices == rightChunkPositionIndices) {
				rightChunkInQueue = true;
			}
			if (chunkGenQueue[i].positionIndices == frontChunkPositionIndices) {
				frontChunkInQueue = true;
			}
			if (chunkGenQueue[i].positionIndices == backChunkPositionIndices) {
				backChunkInQueue = true;
			}
		}

		if (!baseChunk->leftNeighbor && !leftChunkInQueue) {
			chunkGenQueue.push_back({ baseChunk, texAtlasSegment, leftChunkPosition, leftChunkPositionIndices, ChunkNeighborDirection::LEFT });
		}
		if (!baseChunk->rightNeighbor && !rightChunkInQueue) {
			chunkGenQueue.push_back({ baseChunk, texAtlasSegment, rightChunkPosition, rightChunkPositionIndices, ChunkNeighborDirection::RIGHT });
		}
		if (!baseChunk->frontNeighbor && !frontChunkInQueue) {
			chunkGenQueue.push_back({ baseChunk, texAtlasSegment, frontChunkPosition, frontChunkPositionIndices, ChunkNeighborDirection::FRONT });
		}
		if (!baseChunk->backNeighbor && !backChunkInQueue) {
			chunkGenQueue.push_back({ baseChunk, texAtlasSegment, backChunkPosition, backChunkPositionIndices, ChunkNeighborDirection::BACK });
		}
	}
	void WorldGenerator::generateChunksForBaseNeighbors(TextureAtlasSegment *texAtlasSegment, Chunk *baseChunk) {
		if (baseChunk->leftNeighbor) {
			generateChunksFromBase(texAtlasSegment, baseChunk->leftNeighbor);
		}
		if (baseChunk->rightNeighbor) {
			generateChunksFromBase(texAtlasSegment, baseChunk->rightNeighbor);
		}
		if (baseChunk->frontNeighbor) {
			generateChunksFromBase(texAtlasSegment, baseChunk->frontNeighbor);
		}
		if (baseChunk->backNeighbor) {
			generateChunksFromBase(texAtlasSegment, baseChunk->backNeighbor);
		}
	}

	//Public
	void WorldGenerator::generateChunks(TextureAtlasSegment *texAtlasSegment) {
		Chunk *currentChunk = WorldMap::getChunkPtr(player->getChunkIndex());
		
		generateChunksFromBase(texAtlasSegment, currentChunk);
		generateChunksForBaseNeighbors(texAtlasSegment, currentChunk);

		if (currentChunk->leftNeighbor) {
			generateChunksForBaseNeighbors(texAtlasSegment, currentChunk->leftNeighbor);
		}
		if (currentChunk->rightNeighbor) {
			generateChunksForBaseNeighbors(texAtlasSegment, currentChunk->rightNeighbor);
		}
		if (currentChunk->frontNeighbor) {
			generateChunksForBaseNeighbors(texAtlasSegment, currentChunk->frontNeighbor);
		}
		if (currentChunk->backNeighbor) {
			generateChunksForBaseNeighbors(texAtlasSegment, currentChunk->backNeighbor);
		}

		if (chunkGenQueue.size() > 0) {
			Chunk *baseChunk = chunkGenQueue[0].baseChunk;
			switch (chunkGenQueue[0].direction) {
			case ChunkNeighborDirection::LEFT: {
				Chunk *newChunk = new Chunk(chunkGenQueue[0].texAtlasSegment, chunkGenQueue[0].position);
				baseChunk->setLeftNeighbor(newChunk);
				WorldMap::addChunk(newChunk);
				setNeighborChunks(newChunk, true, false, true, true);
				break;
			}
			case ChunkNeighborDirection::RIGHT: {
				Chunk *newChunk = new Chunk(chunkGenQueue[0].texAtlasSegment, chunkGenQueue[0].position);
				baseChunk->setRightNeighbor(newChunk);
				WorldMap::addChunk(newChunk);
				setNeighborChunks(newChunk, false, true, true, true);
				break;
			}
			case ChunkNeighborDirection::FRONT: {
				Chunk *newChunk = new Chunk(chunkGenQueue[0].texAtlasSegment, chunkGenQueue[0].position);
				baseChunk->setFrontNeighbor(newChunk);
				WorldMap::addChunk(newChunk);
				setNeighborChunks(newChunk, true, true, true, false);
				break;
			}
			case ChunkNeighborDirection::BACK: {
				Chunk *newChunk = new Chunk(chunkGenQueue[0].texAtlasSegment, chunkGenQueue[0].position);
				baseChunk->setBackNeighbor(newChunk);
				WorldMap::addChunk(newChunk);
				setNeighborChunks(newChunk, true, true, false, true);
				break;
			}
			}
			chunkGenQueue.erase(chunkGenQueue.begin());
		}
	}
}