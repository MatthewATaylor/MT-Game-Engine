#include "Interaction/Player.h"

namespace mtge {
	//Constructor
	Player::Player(math::Vec3 position, const math::Vec3 DIMENSIONS) : 
		Camera(position, math::Vec3(0.0f, 0.0f, 1.0f)), DIMENSIONS(DIMENSIONS) {}

	//Private
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
	void Player::manageCollisionX(WorldMap *worldMap) {
		for (unsigned int chunkIndex = 0; chunkIndex < worldMap->getNumChunks(); chunkIndex++) {
			for (unsigned int i = 0; i < Chunk::LENGTH_IN_CUBES; i++) {
				for (unsigned int j = 0; j < Chunk::LENGTH_IN_CUBES; j++) {
					for (unsigned int k = 0; k < Chunk::LENGTH_IN_CUBES; k++) {
						Cube *currentCube = worldMap->getChunkPtr(chunkIndex)->getCubePtr(i, j, k);
						if (currentCube->type == 'x') {
							continue;
						}
						
						int chunkLength = (int)Chunk::LENGTH_IN_CUBES;
						float cubeX = -(chunkLength / 2.0f) * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE / 2.0f + i * Chunk::CUBE_SIZE;
						float cubeY = -chunkLength * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE + j * Chunk::CUBE_SIZE;
						float cubeZ = -(chunkLength / 2.0f) * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE / 2.0f + k * Chunk::CUBE_SIZE;

						if (isCubeCollision(math::Vec3(cubeX, cubeY, cubeZ), math::Vec3(Chunk::CUBE_SIZE))) {
							if (totalMovement.getX() > 0) {
								position.setX(cubeX - 0.5f * Chunk::CUBE_SIZE - 0.5f * DIMENSIONS.getX());
							}
							else if (totalMovement.getX() < 0) {
								position.setX(cubeX + 0.5f * Chunk::CUBE_SIZE + 0.5f * DIMENSIONS.getX());
							}
						}
					}
				}
			}
		}
	}
	void Player::manageCollisionY(WorldMap *worldMap) {
		bool bottomCollision = false;
		for (unsigned int chunkIndex = 0; chunkIndex < worldMap->getNumChunks(); chunkIndex++) {
			for (unsigned int i = 0; i < Chunk::LENGTH_IN_CUBES; i++) {
				for (unsigned int j = 0; j < Chunk::LENGTH_IN_CUBES; j++) {
					for (unsigned int k = 0; k < Chunk::LENGTH_IN_CUBES; k++) {
						Cube *currentCube = worldMap->getChunkPtr(chunkIndex)->getCubePtr(i, j, k);
						if (currentCube->type == 'x') {
							continue;
						}

						int chunkLength = (int)Chunk::LENGTH_IN_CUBES;
						float cubeX = -(chunkLength / 2.0f) * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE / 2.0f + i * Chunk::CUBE_SIZE;
						float cubeY = -chunkLength * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE + j * Chunk::CUBE_SIZE;
						float cubeZ = -(chunkLength / 2.0f) * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE / 2.0f + k * Chunk::CUBE_SIZE;

						if (isCubeCollision(math::Vec3(cubeX, cubeY, cubeZ), math::Vec3(Chunk::CUBE_SIZE))) {
							if (totalMovement.getY() > 0) {
								position.setY(cubeY - 0.5f * Chunk::CUBE_SIZE - 0.5f * DIMENSIONS.getY());
								gravitySpeed = 0.0f;
							}
							else if (totalMovement.getY() < 0) {
								position.setY(cubeY + 0.5f * Chunk::CUBE_SIZE + 0.5f * DIMENSIONS.getY());
								gravitySpeed = startGravitySpeed;
								bottomCollision = true;
							}
						}
					}
				}
			}
		}
		onGround = bottomCollision;
	}
	void Player::manageCollisionZ(WorldMap *worldMap) {
		for (unsigned int chunkIndex = 0; chunkIndex < worldMap->getNumChunks(); chunkIndex++) {
			for (unsigned int i = 0; i < Chunk::LENGTH_IN_CUBES; i++) {
				for (unsigned int j = 0; j < Chunk::LENGTH_IN_CUBES; j++) {
					for (unsigned int k = 0; k < Chunk::LENGTH_IN_CUBES; k++) {
						Cube *currentCube = worldMap->getChunkPtr(chunkIndex)->getCubePtr(i, j, k);
						if (currentCube->type == 'x') {
							continue;
						}

						int chunkLength = (int)Chunk::LENGTH_IN_CUBES;
						float cubeX = -(chunkLength / 2.0f) * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE / 2.0f + i * Chunk::CUBE_SIZE;
						float cubeY = -chunkLength * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE + j * Chunk::CUBE_SIZE;
						float cubeZ = -(chunkLength / 2.0f) * Chunk::CUBE_SIZE + Chunk::CUBE_SIZE / 2.0f + k * Chunk::CUBE_SIZE;

						if (isCubeCollision(math::Vec3(cubeX, cubeY, cubeZ), math::Vec3(Chunk::CUBE_SIZE))) {
							if (totalMovement.getZ() > 0) {
								position.setZ(cubeZ - 0.5f * Chunk::CUBE_SIZE - 0.5f * DIMENSIONS.getZ());
							}
							else if (totalMovement.getZ() < 0) {
								position.setZ(cubeZ + 0.5f * Chunk::CUBE_SIZE + 0.5f * DIMENSIONS.getZ());
							}
						}
					}
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
			gravitySpeed = jumpSize;
			onGround = false;
		}
	}
	void Player::controlMotion(Window *window, WorldMap *worldMap, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey) {
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
			position.setY(position.getY() + totalMovement.getY());
			manageCollisionY(worldMap);

			position.setX(position.getX() + totalMovement.getX());
			manageCollisionX(worldMap);

			position.setZ(position.getZ() + totalMovement.getZ());
			manageCollisionZ(worldMap);
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
	math::Mat4 Player::getViewMatrix() {
		math::Vec3 eye(position.getX(), position.getY() + 0.4f * DIMENSIONS.getY(), position.getZ());
		return math::Util::MatGen::lookAt(eye, eye + front, UP_VECTOR);
	}
}