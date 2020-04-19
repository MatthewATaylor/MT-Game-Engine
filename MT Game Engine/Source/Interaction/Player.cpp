#include "Interaction/Player.h"

namespace mtge {
	//Constructor
	Player::Player(math::Vec3 position, const math::Vec3 DIMENSIONS) : 
		Camera(position, math::Vec3(0.0f, 0.0f, 1.0f)), DIMENSIONS(DIMENSIONS) {
		
		playerHeightInCubes = (unsigned int)ceilf(DIMENSIONS.getY() / Chunk::CUBE_SIZE);
	}

	//Private
	math::Vec3 Player::getCubePosFromIndices(math::Vec<unsigned int, 3> indices, unsigned int chunkIndex) {
		int chunkLength = (int)Chunk::LENGTH_IN_CUBES;
		float cubeX =
			-(chunkLength / 2.0f) * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE / 2.0f + indices.getX() * Chunk::CUBE_SIZE +
			WorldMap::getChunkPtr(chunkIndex)->getPosition().getX();
		float cubeY = -chunkLength * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE + indices.getY() * Chunk::CUBE_SIZE;
		float cubeZ = -(chunkLength / 2.0f) * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE / 2.0f + indices.getZ() * Chunk::CUBE_SIZE +
			WorldMap::getChunkPtr(chunkIndex)->getPosition().getY();
		return math::Vec3(cubeX, cubeY, cubeZ);
	}
	void Player::setBottomCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices) {
		if (posIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			if (WorldMap::getChunkPtr(mapChunkIndex)->getCubePtr(posIndices.getX(), posIndices.getY(), posIndices.getZ())->type != 'x') {
				math::Vec3 cubeCoords = getCubePosFromIndices(posIndices, mapChunkIndex);
				collisionCoordsToCheck.push_back(cubeCoords);
			}
		}
	}
	void Player::setTopCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices) {
		for (unsigned int i = 0; i <= jumpHeightInCubes; i++) {
			unsigned int yIndexToTest = posIndices.getY() + playerHeightInCubes + i;
			if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
				math::Vec<unsigned int, 3> indicesToTest(posIndices.getX(), yIndexToTest, posIndices.getZ());
				if (WorldMap::getChunkPtr(mapChunkIndex)->getCubePtr(indicesToTest.getX(), indicesToTest.getY(), indicesToTest.getZ())->type != 'x') {
					math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, mapChunkIndex);
					collisionCoordsToCheck.push_back(cubeCoords);
				}
			}
		}
	}
	void Player::setFrontCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices) {
		if (posIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			unsigned int zIndexToTest = posIndices.getZ() + 1;
			unsigned int chunkIndexToTest = mapChunkIndex;
			if (zIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				if (!WorldMap::getChunkPtr(mapChunkIndex)->frontNeighbor) {
					return;
				}
				zIndexToTest = 0;
				chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->frontNeighbor->indexInMap;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = posIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest(posIndices.getX(), yIndexToTest, zIndexToTest);
					if (WorldMap::getChunkPtr(mapChunkIndex)->getCubePtr(indicesToTest.getX(), indicesToTest.getY(), indicesToTest.getZ())->type != 'x') {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkIndexToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setBackCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices) {
		if (posIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			int zIndexToTest = (int)posIndices.getZ() - 1;
			unsigned int chunkIndexToTest = mapChunkIndex;
			if (zIndexToTest < 0) {
				if (!WorldMap::getChunkPtr(mapChunkIndex)->backNeighbor) {
					return;
				}
				zIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->backNeighbor->indexInMap;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = posIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest(posIndices.getX(), yIndexToTest, (unsigned int)zIndexToTest);
					if (WorldMap::getChunkPtr(mapChunkIndex)->getCubePtr(indicesToTest.getX(), indicesToTest.getY(), indicesToTest.getZ())->type != 'x') {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkIndexToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setLeftCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices) {
		if (posIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			int xIndexToTest = (int)posIndices.getX() - 1;
			unsigned int chunkIndexToTest = mapChunkIndex;
			if (xIndexToTest < 0) {
				if (!WorldMap::getChunkPtr(mapChunkIndex)->leftNeighbor) {
					return;
				}
				xIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->leftNeighbor->indexInMap;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = posIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest((unsigned int)xIndexToTest, yIndexToTest, posIndices.getZ());
					if (WorldMap::getChunkPtr(mapChunkIndex)->getCubePtr(indicesToTest.getX(), indicesToTest.getY(), indicesToTest.getZ())->type != 'x') {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkIndexToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setRightCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices) {
		if (posIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			unsigned int xIndexToTest = posIndices.getX() + 1;
			unsigned int chunkIndexToTest = mapChunkIndex;
			if (xIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				if (!WorldMap::getChunkPtr(mapChunkIndex)->rightNeighbor) {
					return;
				}
				xIndexToTest = 0;
				chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->rightNeighbor->indexInMap;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = posIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest(xIndexToTest, yIndexToTest, posIndices.getZ());
					if (WorldMap::getChunkPtr(mapChunkIndex)->getCubePtr(indicesToTest.getX(), indicesToTest.getY(), indicesToTest.getZ())->type != 'x') {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkIndexToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setFrontRightCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices) {
		if (posIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			unsigned int xIndexToTest = posIndices.getX() + 1;
			unsigned int zIndexToTest = posIndices.getZ() + 1;
			unsigned int chunkIndexToTest = mapChunkIndex;

			if (xIndexToTest >= Chunk::LENGTH_IN_CUBES && zIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				xIndexToTest = 0;
				zIndexToTest = 0;
				if (!WorldMap::getChunkPtr(mapChunkIndex)->rightNeighbor || 
					!WorldMap::getChunkPtr(mapChunkIndex)->rightNeighbor->frontNeighbor) {

					if (!WorldMap::getChunkPtr(mapChunkIndex)->frontNeighbor ||
						!WorldMap::getChunkPtr(mapChunkIndex)->frontNeighbor->rightNeighbor) {

						return;
					}
					else {
						chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->frontNeighbor->rightNeighbor->indexInMap;
					}
				}
				else {
					chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->rightNeighbor->frontNeighbor->indexInMap;
				}
			}
			else if (xIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				if (!WorldMap::getChunkPtr(mapChunkIndex)->rightNeighbor) {
					return;
				}
				xIndexToTest = 0;
				chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->rightNeighbor->indexInMap;
			}
			else if (zIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				if (!WorldMap::getChunkPtr(mapChunkIndex)->frontNeighbor) {
					return;
				}
				zIndexToTest = 0;
				chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->frontNeighbor->indexInMap;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = posIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest(xIndexToTest, yIndexToTest, zIndexToTest);
					if (WorldMap::getChunkPtr(mapChunkIndex)->getCubePtr(indicesToTest.getX(), indicesToTest.getY(), indicesToTest.getZ())->type != 'x') {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkIndexToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setBackRightCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices) {
		if (posIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			unsigned int xIndexToTest = posIndices.getX() + 1;
			int zIndexToTest = (int)posIndices.getZ() - 1;
			unsigned int chunkIndexToTest = mapChunkIndex;

			if (xIndexToTest >= Chunk::LENGTH_IN_CUBES && zIndexToTest < 0) {
				xIndexToTest = 0;
				zIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				if (!WorldMap::getChunkPtr(mapChunkIndex)->rightNeighbor ||
					!WorldMap::getChunkPtr(mapChunkIndex)->rightNeighbor->backNeighbor) {

					if (!WorldMap::getChunkPtr(mapChunkIndex)->backNeighbor ||
						!WorldMap::getChunkPtr(mapChunkIndex)->backNeighbor->rightNeighbor) {

						return;
					}
					else {
						chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->backNeighbor->rightNeighbor->indexInMap;
					}
				}
				else {
					chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->rightNeighbor->backNeighbor->indexInMap;
				}
			}
			else if (xIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				if (!WorldMap::getChunkPtr(mapChunkIndex)->rightNeighbor) {
					return;
				}
				xIndexToTest = 0;
				chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->rightNeighbor->indexInMap;
			}
			else if (zIndexToTest < 0) {
				if (!WorldMap::getChunkPtr(mapChunkIndex)->backNeighbor) {
					return;
				}
				zIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->backNeighbor->indexInMap;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = posIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest(xIndexToTest, yIndexToTest, (unsigned int)zIndexToTest);
					if (WorldMap::getChunkPtr(mapChunkIndex)->getCubePtr(indicesToTest.getX(), indicesToTest.getY(), indicesToTest.getZ())->type != 'x') {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkIndexToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setFrontLeftCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices) {
		if (posIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			int xIndexToTest = posIndices.getX() - 1;
			unsigned int zIndexToTest = posIndices.getZ() + 1;
			unsigned int chunkIndexToTest = mapChunkIndex;

			if (xIndexToTest < 0 && zIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				xIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				zIndexToTest = 0;
				if (!WorldMap::getChunkPtr(mapChunkIndex)->leftNeighbor ||
					!WorldMap::getChunkPtr(mapChunkIndex)->leftNeighbor->frontNeighbor) {

					if (!WorldMap::getChunkPtr(mapChunkIndex)->frontNeighbor ||
						!WorldMap::getChunkPtr(mapChunkIndex)->frontNeighbor->leftNeighbor) {

						return;
					}
					else {
						chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->frontNeighbor->leftNeighbor->indexInMap;
					}
				}
				else {
					chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->leftNeighbor->frontNeighbor->indexInMap;
				}
			}
			else if (xIndexToTest < 0) {
				if (!WorldMap::getChunkPtr(mapChunkIndex)->leftNeighbor) {
					return;
				}
				xIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->leftNeighbor->indexInMap;
			}
			else if (zIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				if (!WorldMap::getChunkPtr(mapChunkIndex)->frontNeighbor) {
					return;
				}
				zIndexToTest = 0;
				chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->frontNeighbor->indexInMap;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = posIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest((unsigned int)xIndexToTest, yIndexToTest, zIndexToTest);
					if (WorldMap::getChunkPtr(mapChunkIndex)->getCubePtr(indicesToTest.getX(), indicesToTest.getY(), indicesToTest.getZ())->type != 'x') {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkIndexToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setBackLeftCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices) {
		if (posIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			int xIndexToTest = posIndices.getX() - 1;
			int zIndexToTest = posIndices.getZ() - 1;
			unsigned int chunkIndexToTest = mapChunkIndex;

			if (xIndexToTest < 0 && zIndexToTest < 0) {
				xIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				zIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				if (!WorldMap::getChunkPtr(mapChunkIndex)->leftNeighbor ||
					!WorldMap::getChunkPtr(mapChunkIndex)->leftNeighbor->backNeighbor) {

					if (!WorldMap::getChunkPtr(mapChunkIndex)->backNeighbor ||
						!WorldMap::getChunkPtr(mapChunkIndex)->backNeighbor->leftNeighbor) {

						return;
					}
					else {
						chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->backNeighbor->leftNeighbor->indexInMap;
					}
				}
				else {
					chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->leftNeighbor->backNeighbor->indexInMap;
				}
			}
			else if (xIndexToTest < 0) {
				if (!WorldMap::getChunkPtr(mapChunkIndex)->leftNeighbor) {
					return;
				}
				xIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->leftNeighbor->indexInMap;
			}
			else if (zIndexToTest < 0) {
				if (!WorldMap::getChunkPtr(mapChunkIndex)->backNeighbor) {
					return;
				}
				zIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				chunkIndexToTest = WorldMap::getChunkPtr(mapChunkIndex)->backNeighbor->indexInMap;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = posIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest((unsigned int)xIndexToTest, yIndexToTest, (unsigned int)zIndexToTest);
					if (WorldMap::getChunkPtr(mapChunkIndex)->getCubePtr(indicesToTest.getX(), indicesToTest.getY(), indicesToTest.getZ())->type != 'x') {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkIndexToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setCollisionCoordsToCheck() {
		collisionCoordsToCheck.clear();
		math::Vec<unsigned int, 3> posIndices = getPositionIndices();
		
		setBottomCollisionCoordsToCheck(posIndices);
		setTopCollisionCoordsToCheck(posIndices);
		setFrontCollisionCoordsToCheck(posIndices);
		setBackCollisionCoordsToCheck(posIndices);
		setLeftCollisionCoordsToCheck(posIndices);
		setRightCollisionCoordsToCheck(posIndices);
		setFrontRightCollisionCoordsToCheck(posIndices);
		setBackRightCollisionCoordsToCheck(posIndices);
		setFrontLeftCollisionCoordsToCheck(posIndices);
		setBackLeftCollisionCoordsToCheck(posIndices);
	}
	bool Player::isCubeCollision(math::Vec3 cubePos, math::Vec3 cubeDimens) {
		//Positions refer to center point
		if (position.getX() + 0.5f * DIMENSIONS.getX() > cubePos.getX() - 0.4999f /* (floating point numbers are fun...) */ * cubeDimens.getX() &&
			position.getX() - 0.5f * DIMENSIONS.getX() < cubePos.getX() + 0.4999f * cubeDimens.getX() &&
			position.getY() + 0.5f * DIMENSIONS.getY() > cubePos.getY() - 0.4999f * cubeDimens.getY() &&
			position.getY() - 0.5f * DIMENSIONS.getY() < cubePos.getY() + 0.4999f * cubeDimens.getY() &&
			position.getZ() + 0.5f * DIMENSIONS.getZ() > cubePos.getZ() - 0.4999f * cubeDimens.getZ() &&
			position.getZ() - 0.5f * DIMENSIONS.getZ() < cubePos.getZ() + 0.4999f * cubeDimens.getZ()) {

			return true;
		}
		return false;
	}
	void Player::manageCollisionX() {
		for (unsigned int i = 0; i < collisionCoordsToCheck.size(); i++) {
			if (isCubeCollision(collisionCoordsToCheck[i], math::Vec3(Chunk::CUBE_SIZE))) {
				if (totalMovement.getX() > 0) {
					position.setX(collisionCoordsToCheck[i].getX() - 0.5f * Chunk::CUBE_SIZE - 0.5f * DIMENSIONS.getX());
					return;
				}
				else if (totalMovement.getX() < 0) {
					position.setX(collisionCoordsToCheck[i].getX() + 0.5f * Chunk::CUBE_SIZE + 0.5f * DIMENSIONS.getX());
					return;
				}
			}
		}
	}
	void Player::manageCollisionY() {
		for (unsigned int i = 0; i < collisionCoordsToCheck.size(); i++) {
			if (isCubeCollision(collisionCoordsToCheck[i], math::Vec3(Chunk::CUBE_SIZE))) {
				if (totalMovement.getY() > 0) {
					position.setY(collisionCoordsToCheck[i].getY() - 0.5f * Chunk::CUBE_SIZE - 0.5f * DIMENSIONS.getY());
					gravitySpeed = 0.0f;
					onGround = false;
					return;
				}
				else if (totalMovement.getY() < 0) {
					position.setY(collisionCoordsToCheck[i].getY() + 0.5f * Chunk::CUBE_SIZE + 0.5f * DIMENSIONS.getY());
					gravitySpeed = startGravitySpeed;
					onGround = true;
					return;
				}
			}
		}
		onGround = false;
	}
	void Player::manageCollisionZ() {
		for (unsigned int i = 0; i < collisionCoordsToCheck.size(); i++) {
			if (isCubeCollision(collisionCoordsToCheck[i], math::Vec3(Chunk::CUBE_SIZE))) {
				if (totalMovement.getZ() > 0) {
					position.setZ(collisionCoordsToCheck[i].getZ() - 0.5f * Chunk::CUBE_SIZE - 0.5f * DIMENSIONS.getZ());
					return;
				}
				else if (totalMovement.getZ() < 0) {
					position.setZ(collisionCoordsToCheck[i].getZ() + 0.5f * Chunk::CUBE_SIZE + 0.5f * DIMENSIONS.getZ());
					return;
				}
			}
		}
	}
	void Player::applyGravity() {
		gravitySpeed += gravityAddend * movementSize;

		if (gravitySpeed > maxGravity) {
			gravitySpeed = maxGravity;
		}

		totalMovement.setY(totalMovement.getY() - gravitySpeed * movementSize);
	}
	math::Vec<int, 2> Player::getChunkPositionIndices() {
		float xRelToCorner = position.getX() + Chunk::CHUNK_SIZE / 2.0f;
		int chunkXIndex = (int)(xRelToCorner / Chunk::CHUNK_SIZE) - (xRelToCorner < 0 ? 1 : 0);

		float zRelToCorner = position.getZ() + Chunk::CHUNK_SIZE / 2.0f;
		int chunkZIndex = (int)(zRelToCorner / Chunk::CHUNK_SIZE) - (zRelToCorner < 0 ? 1 : 0);

		return math::Vec<int, 2>(chunkXIndex, chunkZIndex);
	}
	math::Vec<unsigned int, 3> Player::getPositionIndices() {
		int chunkXIndex = getChunkPositionIndices().getX();
		int chunkZIndex = getChunkPositionIndices().getY();
		float chunkX = chunkXIndex * Chunk::CHUNK_SIZE;
		float chunkZ = chunkZIndex * Chunk::CHUNK_SIZE;
		float xRel = position.getX() - chunkX + Chunk::CHUNK_SIZE / 2.0f;
		float zRel = position.getZ() - chunkZ + Chunk::CHUNK_SIZE / 2.0f;
		int xIndex = (int)(xRel / Chunk::CUBE_SIZE);
		int yIndex = (int)((position.getY() - DIMENSIONS.getY() / 2.0f + Chunk::CHUNK_SIZE) / Chunk::CUBE_SIZE) - 1;
		int zIndex = (int)(zRel / Chunk::CUBE_SIZE);
		xIndex = xIndex < 0 ? 0 : xIndex;
		yIndex = yIndex < 0 ? 0 : yIndex;
		zIndex = zIndex < 0 ? 0 : zIndex;
		return math::Vec<unsigned int, 3>(xIndex, yIndex, zIndex);
	}
	void Player::setMapChunkIndex() {
		math::Vec<int, 2> currentChunkIndices = getChunkPositionIndices();
		Chunk *currentChunk = WorldMap::getChunkPtr(mapChunkIndex);
		if (currentChunkIndices.getX() - prevChunkIndices.getX() > 0 && currentChunk->rightNeighbor) {
			mapChunkIndex = currentChunk->rightNeighbor->indexInMap;
			prevChunkIndices = currentChunkIndices;
		}
		else if (currentChunkIndices.getX() - prevChunkIndices.getX() < 0 && currentChunk->leftNeighbor) {
			mapChunkIndex = currentChunk->leftNeighbor->indexInMap;
			prevChunkIndices = currentChunkIndices;
		}
		else if (currentChunkIndices.getY() - prevChunkIndices.getY() > 0 && currentChunk->frontNeighbor) {
			mapChunkIndex = currentChunk->frontNeighbor->indexInMap;
			prevChunkIndices = currentChunkIndices;
		}
		else if (currentChunkIndices.getY() - prevChunkIndices.getY() < 0 && currentChunk->backNeighbor) {
			mapChunkIndex = currentChunk->backNeighbor->indexInMap;
			prevChunkIndices = currentChunkIndices;
		}
	}

	//Public
	void Player::setCanApplyCollisions(bool canApplyCollisions) {
		this->canApplyCollisions = canApplyCollisions;
	}
	void Player::setCanApplyGravity(bool canApplyGravity) {
		this->canApplyGravity = canApplyGravity;
	}
	void Player::setGravityParams(float startGravitySpeed, float gravityAddend, float maxGravity) {
		this->startGravitySpeed = startGravitySpeed;
		gravitySpeed = startGravitySpeed;

		this->gravityAddend = gravityAddend;
		this->maxGravity = maxGravity;
	}
	void Player::controlJump(Window *window, float jumpSize, int jumpKey) {
		if ((glfwGetKey(window->getPtr_GLFW(), jumpKey) == GLFW_PRESS) && onGround) {
			gravitySpeed = -jumpSize;
			onGround = false;

			float timeToChangeDirection = jumpSize / (gravityAddend * movementSize);
			float jumpYDisplacement = 0.5f * timeToChangeDirection * jumpSize * movementSize;
			if (jumpYDisplacement > 0) {
				jumpHeightInCubes = (unsigned int)ceilf(jumpYDisplacement / Chunk::CUBE_SIZE);
			}
			else {
				jumpHeightInCubes = 0;
			}
		}
	}
	void Player::controlMotion(Window *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey) {
		math::Vec3 movementDirection = math::Vec3(front.getX(), 0.0f, front.getZ());
		controlRawMotion(window, speed, forwardKey, reverseKey, leftKey, rightKey, movementDirection);

		if (canApplyGravity) {
			applyGravity();
		}

		//Normalize X/Z Plane Velocities
		float movementAngle = atan2(totalMovement.getZ(), totalMovement.getX());
		float sinTheta = sin(movementAngle);
		float movementMagnitude = (sinTheta != 0) ? (totalMovement.getZ() / sinTheta) : totalMovement.getX();
		totalMovement.setX(totalMovement.getX() * ((movementMagnitude != 0) ? (movementSize / movementMagnitude) : 0));
		totalMovement.setZ(totalMovement.getZ() * ((movementMagnitude != 0) ? (movementSize / movementMagnitude) : 0));

		if (canApplyCollisions) {
			setCollisionCoordsToCheck();

			position.setY(position.getY() + totalMovement.getY());
			manageCollisionY();

			position.setX(position.getX() + totalMovement.getX());
			manageCollisionX();

			position.setZ(position.getZ() + totalMovement.getZ());
			manageCollisionZ();
		}
		else {
			position += totalMovement;
		}
		
		setMapChunkIndex();
	}
	void Player::controlReset(Window *window, float resetHeight) {
		if (glfwGetKey(window->getPtr_GLFW(), GLFW_KEY_R) == GLFW_PRESS) {
			gravitySpeed = startGravitySpeed;
			position = math::Vec3(0.0f, resetHeight, 0.0f);
			mapChunkIndex = 0;
			prevChunkIndices = math::Vec<int, 2>(0, 0);
		}
	}
	math::Mat4 Player::getViewMatrix() {
		math::Vec3 eye(position.getX(), position.getY() + 0.4f * DIMENSIONS.getY(), position.getZ());
		return math::Util::MatGen::lookAt(eye, eye + front, UP_VECTOR);
	}
}