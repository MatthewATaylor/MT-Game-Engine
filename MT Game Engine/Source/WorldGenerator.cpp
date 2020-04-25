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
	void WorldGenerator::generateChunksFromBase(CubeCharacterizer *cubeCharacterizer, Chunk *baseChunk) {
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
			chunkGenQueue.push_back({ baseChunk, cubeCharacterizer, leftChunkPosition, leftChunkPositionIndices, ChunkNeighborDirection::LEFT });
		}
		if (!baseChunk->rightNeighbor && !rightChunkInQueue) {
			chunkGenQueue.push_back({ baseChunk, cubeCharacterizer, rightChunkPosition, rightChunkPositionIndices, ChunkNeighborDirection::RIGHT });
		}
		if (!baseChunk->frontNeighbor && !frontChunkInQueue) {
			chunkGenQueue.push_back({ baseChunk, cubeCharacterizer, frontChunkPosition, frontChunkPositionIndices, ChunkNeighborDirection::FRONT });
		}
		if (!baseChunk->backNeighbor && !backChunkInQueue) {
			chunkGenQueue.push_back({ baseChunk, cubeCharacterizer, backChunkPosition, backChunkPositionIndices, ChunkNeighborDirection::BACK });
		}
	}
	void WorldGenerator::generateChunksForBaseNeighbors(CubeCharacterizer *cubeCharacterizer, Chunk *baseChunk) {
		if (baseChunk->leftNeighbor) {
			generateChunksFromBase(cubeCharacterizer, baseChunk->leftNeighbor);
		}
		if (baseChunk->rightNeighbor) {
			generateChunksFromBase(cubeCharacterizer, baseChunk->rightNeighbor);
		}
		if (baseChunk->frontNeighbor) {
			generateChunksFromBase(cubeCharacterizer, baseChunk->frontNeighbor);
		}
		if (baseChunk->backNeighbor) {
			generateChunksFromBase(cubeCharacterizer, baseChunk->backNeighbor);
		}
	}

	//Public
	void WorldGenerator::generateChunks(CubeCharacterizer *cubeCharacterizer) {
		Chunk *currentChunk = WorldMap::getChunkPtr(player->getChunkIndex());
		
		generateChunksFromBase(cubeCharacterizer, currentChunk);
		generateChunksForBaseNeighbors(cubeCharacterizer, currentChunk);

		if (currentChunk->leftNeighbor) {
			generateChunksForBaseNeighbors(cubeCharacterizer, currentChunk->leftNeighbor);
		}
		if (currentChunk->rightNeighbor) {
			generateChunksForBaseNeighbors(cubeCharacterizer, currentChunk->rightNeighbor);
		}
		if (currentChunk->frontNeighbor) {
			generateChunksForBaseNeighbors(cubeCharacterizer, currentChunk->frontNeighbor);
		}
		if (currentChunk->backNeighbor) {
			generateChunksForBaseNeighbors(cubeCharacterizer, currentChunk->backNeighbor);
		}

		if (chunkGenQueue.size() > 0) {
			Chunk *baseChunk = chunkGenQueue[0].baseChunk;
			switch (chunkGenQueue[0].direction) {
			case ChunkNeighborDirection::LEFT: {
				Chunk *newChunk = new Chunk(chunkGenQueue[0].cubeCharacterizer, chunkGenQueue[0].position);
				baseChunk->setLeftNeighbor(newChunk);
				WorldMap::addChunk(newChunk);
				setNeighborChunks(newChunk, true, false, true, true);
				break;
			}
			case ChunkNeighborDirection::RIGHT: {
				Chunk *newChunk = new Chunk(chunkGenQueue[0].cubeCharacterizer, chunkGenQueue[0].position);
				baseChunk->setRightNeighbor(newChunk);
				WorldMap::addChunk(newChunk);
				setNeighborChunks(newChunk, false, true, true, true);
				break;
			}
			case ChunkNeighborDirection::FRONT: {
				Chunk *newChunk = new Chunk(chunkGenQueue[0].cubeCharacterizer, chunkGenQueue[0].position);
				baseChunk->setFrontNeighbor(newChunk);
				WorldMap::addChunk(newChunk);
				setNeighborChunks(newChunk, true, true, true, false);
				break;
			}
			case ChunkNeighborDirection::BACK: {
				Chunk *newChunk = new Chunk(chunkGenQueue[0].cubeCharacterizer, chunkGenQueue[0].position);
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