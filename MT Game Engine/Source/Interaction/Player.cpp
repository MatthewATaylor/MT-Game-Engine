#include "Interaction/Player.h"

namespace mtge {
	//Constructor
	Player::Player(math::Vec3 position, const math::Vec3 DIMENSIONS) : 
		Camera(position, math::Vec3(0.0f, 0.0f, 1.0f)), DIMENSIONS(DIMENSIONS) {
		
		playerHeightInCubes = (unsigned int)ceilf(DIMENSIONS.getY() / Chunk::CUBE_SIZE);
	}

	//Private
	math::Vec3 Player::getCubePosFromIndices(const math::Vec<unsigned int, 3> &indices, Chunk *chunk) {
		int chunkLength = (int)Chunk::LENGTH_IN_CUBES;
		float cubeX =
			-(chunkLength / 2.0f) * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE / 2.0f + indices.getX() * Chunk::CUBE_SIZE +
			chunk->getPosition().getX();
		float cubeY = -chunkLength * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE + indices.getY() * Chunk::CUBE_SIZE;
		float cubeZ = -(chunkLength / 2.0f) * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE / 2.0f + indices.getZ() * Chunk::CUBE_SIZE +
			chunk->getPosition().getY();
		return math::Vec3(cubeX, cubeY, cubeZ);
	}
	
	void Player::setBottomCollisionCoordsToCheck() {
		if (positionIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			if (currentChunk->getCubePtr(positionIndices)) {
				math::Vec3 cubeCoords = getCubePosFromIndices(positionIndices, currentChunk);
				collisionCoordsToCheck.push_back(cubeCoords);
			}
		}
	}
	void Player::setTopCollisionCoordsToCheck() {
		for (unsigned int i = 0; i <= jumpHeightInCubes; i++) {
			unsigned int yIndexToTest = positionIndices.getY() + playerHeightInCubes + i;
			if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
				math::Vec<unsigned int, 3> indicesToTest(positionIndices.getX(), yIndexToTest, positionIndices.getZ());
				if (currentChunk->getCubePtr(indicesToTest)) {
					math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, currentChunk);
					collisionCoordsToCheck.push_back(cubeCoords);
				}
			}
		}
	}
	void Player::setFrontCollisionCoordsToCheck() {
		if (positionIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			unsigned int zIndexToTest = positionIndices.getZ() + 1;
			Chunk *chunkToTest = currentChunk;
			if (zIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				if (!currentChunk->frontNeighbor) {
					return;
				}
				zIndexToTest = 0;
				chunkToTest = currentChunk->frontNeighbor;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = positionIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest(positionIndices.getX(), yIndexToTest, zIndexToTest);
					if (chunkToTest->getCubePtr(indicesToTest)) {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setBackCollisionCoordsToCheck() {
		if (positionIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			int zIndexToTest = (int)positionIndices.getZ() - 1;
			Chunk *chunkToTest = currentChunk;
			if (zIndexToTest < 0) {
				if (!currentChunk->backNeighbor) {
					return;
				}
				zIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				chunkToTest = currentChunk->backNeighbor;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = positionIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest(positionIndices.getX(), yIndexToTest, (unsigned int)zIndexToTest);
					if (chunkToTest->getCubePtr(indicesToTest)) {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setLeftCollisionCoordsToCheck() {
		if (positionIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			int xIndexToTest = (int)positionIndices.getX() - 1;
			Chunk *chunkToTest = currentChunk;
			if (xIndexToTest < 0) {
				if (!currentChunk->leftNeighbor) {
					return;
				}
				xIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				chunkToTest = currentChunk->leftNeighbor;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = positionIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest((unsigned int)xIndexToTest, yIndexToTest, positionIndices.getZ());
					if (chunkToTest->getCubePtr(indicesToTest)) {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setRightCollisionCoordsToCheck() {
		if (positionIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			unsigned int xIndexToTest = positionIndices.getX() + 1;
			Chunk *chunkToTest = currentChunk;
			if (xIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				if (!currentChunk->rightNeighbor) {
					return;
				}
				xIndexToTest = 0;
				chunkToTest = currentChunk->rightNeighbor;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = positionIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest(xIndexToTest, yIndexToTest, positionIndices.getZ());
					if (chunkToTest->getCubePtr(indicesToTest)) {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setFrontRightCollisionCoordsToCheck() {
		if (positionIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			unsigned int xIndexToTest = positionIndices.getX() + 1;
			unsigned int zIndexToTest = positionIndices.getZ() + 1;
			Chunk *chunkToTest = currentChunk;

			if (xIndexToTest >= Chunk::LENGTH_IN_CUBES && zIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				xIndexToTest = 0;
				zIndexToTest = 0;
				if (!currentChunk->rightNeighbor ||
					!currentChunk->rightNeighbor->frontNeighbor) {

					if (!currentChunk->frontNeighbor ||
						!currentChunk->frontNeighbor->rightNeighbor) {

						return;
					}
					else {
						chunkToTest = currentChunk->frontNeighbor->rightNeighbor;
					}
				}
				else {
					chunkToTest = currentChunk->rightNeighbor->frontNeighbor;
				}
			}
			else if (xIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				if (!currentChunk->rightNeighbor) {
					return;
				}
				xIndexToTest = 0;
				chunkToTest = currentChunk->rightNeighbor;
			}
			else if (zIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				if (!currentChunk->frontNeighbor) {
					return;
				}
				zIndexToTest = 0;
				chunkToTest = currentChunk->frontNeighbor;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = positionIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest(xIndexToTest, yIndexToTest, zIndexToTest);
					if (chunkToTest->getCubePtr(indicesToTest)) {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setBackRightCollisionCoordsToCheck() {
		if (positionIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			unsigned int xIndexToTest = positionIndices.getX() + 1;
			int zIndexToTest = (int)positionIndices.getZ() - 1;
			Chunk *chunkToTest = currentChunk;

			if (xIndexToTest >= Chunk::LENGTH_IN_CUBES && zIndexToTest < 0) {
				xIndexToTest = 0;
				zIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				if (!currentChunk->rightNeighbor ||
					!currentChunk->rightNeighbor->backNeighbor) {

					if (!currentChunk->backNeighbor ||
						!currentChunk->backNeighbor->rightNeighbor) {

						return;
					}
					else {
						chunkToTest = currentChunk->backNeighbor->rightNeighbor;
					}
				}
				else {
					chunkToTest = currentChunk->rightNeighbor->backNeighbor;
				}
			}
			else if (xIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				if (!currentChunk->rightNeighbor) {
					return;
				}
				xIndexToTest = 0;
				chunkToTest = currentChunk->rightNeighbor;
			}
			else if (zIndexToTest < 0) {
				if (!currentChunk->backNeighbor) {
					return;
				}
				zIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				chunkToTest = currentChunk->backNeighbor;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = positionIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest(xIndexToTest, yIndexToTest, (unsigned int)zIndexToTest);
					if (chunkToTest->getCubePtr(indicesToTest)) {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setFrontLeftCollisionCoordsToCheck() {
		if (positionIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			int xIndexToTest = positionIndices.getX() - 1;
			unsigned int zIndexToTest = positionIndices.getZ() + 1;
			Chunk *chunkToTest = currentChunk;

			if (xIndexToTest < 0 && zIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				xIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				zIndexToTest = 0;
				if (!currentChunk->leftNeighbor ||
					!currentChunk->leftNeighbor->frontNeighbor) {

					if (!currentChunk->frontNeighbor ||
						!currentChunk->frontNeighbor->leftNeighbor) {

						return;
					}
					else {
						chunkToTest = currentChunk->frontNeighbor->leftNeighbor;
					}
				}
				else {
					chunkToTest = currentChunk->leftNeighbor->frontNeighbor;
				}
			}
			else if (xIndexToTest < 0) {
				if (!currentChunk->leftNeighbor) {
					return;
				}
				xIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				chunkToTest = currentChunk->leftNeighbor;
			}
			else if (zIndexToTest >= Chunk::LENGTH_IN_CUBES) {
				if (!currentChunk->frontNeighbor) {
					return;
				}
				zIndexToTest = 0;
				chunkToTest = currentChunk->frontNeighbor;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = positionIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest((unsigned int)xIndexToTest, yIndexToTest, zIndexToTest);
					if (chunkToTest->getCubePtr(indicesToTest)) {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	void Player::setBackLeftCollisionCoordsToCheck() {
		if (positionIndices.getY() < Chunk::LENGTH_IN_CUBES) {
			int xIndexToTest = positionIndices.getX() - 1;
			int zIndexToTest = positionIndices.getZ() - 1;
			Chunk *chunkToTest = currentChunk;

			if (xIndexToTest < 0 && zIndexToTest < 0) {
				xIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				zIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				if (!currentChunk->leftNeighbor ||
					!currentChunk->leftNeighbor->backNeighbor) {

					if (!currentChunk->backNeighbor ||
						!currentChunk->backNeighbor->leftNeighbor) {

						return;
					}
					else {
						chunkToTest = currentChunk->backNeighbor->leftNeighbor;
					}
				}
				else {
					chunkToTest = currentChunk->leftNeighbor->backNeighbor;
				}
			}
			else if (xIndexToTest < 0) {
				if (!currentChunk->leftNeighbor) {
					return;
				}
				xIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				chunkToTest = currentChunk->leftNeighbor;
			}
			else if (zIndexToTest < 0) {
				if (!currentChunk->backNeighbor) {
					return;
				}
				zIndexToTest = Chunk::LENGTH_IN_CUBES - 1;
				chunkToTest = currentChunk->backNeighbor;
			}
			for (unsigned int i = 0; i <= playerHeightInCubes + 1; i++) {
				unsigned int yIndexToTest = positionIndices.getY() + i;
				if (yIndexToTest < Chunk::LENGTH_IN_CUBES) {
					math::Vec<unsigned int, 3> indicesToTest((unsigned int)xIndexToTest, yIndexToTest, (unsigned int)zIndexToTest);
					if (chunkToTest->getCubePtr(indicesToTest)) {
						math::Vec3 cubeCoords = getCubePosFromIndices(indicesToTest, chunkToTest);
						collisionCoordsToCheck.push_back(cubeCoords);
					}
				}
			}
		}
	}
	
	void Player::setCollisionCoordsToCheck() {
		collisionCoordsToCheck.clear();
		if (!currentChunk) {
			return;
		}

		setBottomCollisionCoordsToCheck();
		setTopCollisionCoordsToCheck();
		setFrontCollisionCoordsToCheck();
		setBackCollisionCoordsToCheck();
		setLeftCollisionCoordsToCheck();
		setRightCollisionCoordsToCheck();
		setFrontRightCollisionCoordsToCheck();
		setBackRightCollisionCoordsToCheck();
		setFrontLeftCollisionCoordsToCheck();
		setBackLeftCollisionCoordsToCheck();
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
	void Player::reduceMotion() {
		for (unsigned int i = 0; i < 3; i++) {
			float maxSpeed = Chunk::CUBE_SIZE;
			if (totalMovement.get(i) > maxSpeed) {
				totalMovement.set(i, maxSpeed);
			}
			else if (totalMovement.get(i) < -maxSpeed) {
				totalMovement.set(i, -maxSpeed);
			}
		}
	}
	void Player::setCurrentChunk() {
		float xRelToCorner = position.getX() + Chunk::CHUNK_SIZE / 2.0f;
		int chunkXIndex = (int)(xRelToCorner / Chunk::CHUNK_SIZE) - (xRelToCorner < 0 ? 1 : 0);

		float zRelToCorner = position.getZ() + Chunk::CHUNK_SIZE / 2.0f;
		int chunkZIndex = (int)(zRelToCorner / Chunk::CHUNK_SIZE) - (zRelToCorner < 0 ? 1 : 0);

		Chunk *newCurrentChunk = WorldMap::getChunkPtr(math::Vec<int, 2>(chunkXIndex, chunkZIndex));
		if (newCurrentChunk) {
			currentChunk = newCurrentChunk;
		}
	}
	void Player::setPositionIndices() {
		if (currentChunk) {
			int chunkXIndex = currentChunk->getPositionIndices().getX();
			int chunkZIndex = currentChunk->getPositionIndices().getY();
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
			positionIndices = math::Vec<unsigned int, 3>(xIndex, yIndex, zIndex);
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
		setCurrentChunk();
		setPositionIndices();

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

		//Reduce speed for accurate collision detection
		reduceMotion();

		if (canApplyCollisions) {
			setCollisionCoordsToCheck();

			position.setY(position.getY() + totalMovement.getY());
			manageCollisionY();

			position.setZ(position.getZ() + totalMovement.getZ());
			manageCollisionZ();

			position.setX(position.getX() + totalMovement.getX());
			manageCollisionX();
		}
		else {
			position += totalMovement;
		}
	}
	void Player::controlReset(Window *window, float resetHeight) {
		if (glfwGetKey(window->getPtr_GLFW(), GLFW_KEY_R) == GLFW_PRESS) {
			gravitySpeed = startGravitySpeed;
			position = math::Vec3(0.0f, resetHeight, 0.0f);
		}
	}
	math::Vec3 Player::getPosition() {
		return position;
	}
	Chunk *Player::getCurrentChunk() {
		return currentChunk;
	}
	math::Mat4 Player::getViewMatrix() {
		math::Vec3 eye(position.getX(), position.getY() + 0.4f * DIMENSIONS.getY(), position.getZ());
		return math::Util::MatGen::lookAt(eye, eye + front, UP_VECTOR);
	}
}