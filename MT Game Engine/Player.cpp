#include "Player.h"

namespace mtge {
	//Constructor
	Player::Player(glm::vec3 position, const glm::vec3 DIMENSIONS) : Camera(position, glm::vec3(0.0f, 0.0f, -1.0f)), DIMENSIONS(DIMENSIONS) {}

	//Private
	void Player::applyGravity(glm::vec3 *totalMovement, float movementSize) {
		const float GRAVITY_ADDER = 0.35f;
		const float MAX_GRAVITY = 4.0f;
		gravitySpeed += GRAVITY_ADDER * movementSize;

		if (gravitySpeed >= MAX_GRAVITY) {
			gravitySpeed = MAX_GRAVITY;
		}

		totalMovement->y -= gravitySpeed * movementSize;
	}
	void Player::manageCollisionX(glm::vec3 *totalMovement) {
		for (unsigned int i = 0; i < Map::chunks.size(); i++) {
			Chunk *currentChunk = Map::chunks[i];
			int collisionValue = currentChunk->collision(cameraPosition, DIMENSIONS);
			if (collisionValue >= 0) {
				Shape *currentShape = currentChunk->shapes[collisionValue];
				if (totalMovement->x > 0) {
					cameraPosition.x = currentShape->translatedPos.x - 0.5f * currentShape->scaledDimensions.x - 0.5f * DIMENSIONS.x;
				}
				else if (totalMovement->x < 0) {
					cameraPosition.x = currentShape->translatedPos.x + 0.5f * currentShape->scaledDimensions.x + 0.5f * DIMENSIONS.x;
				}
			}
		}
	}
	void Player::manageCollisionY(glm::vec3 *totalMovement, bool *onGround) {
		bool bottomCollision = false;
		for (unsigned int i = 0; i < Map::chunks.size(); i++) {
			Chunk *currentChunk = Map::chunks[i];
			int collisionValue = currentChunk->collision(cameraPosition, DIMENSIONS);
			if (collisionValue >= 0) {
				Shape *currentShape = currentChunk->shapes[collisionValue];
				if (totalMovement->y > 0) {
					cameraPosition.y = currentShape->translatedPos.y - 0.5f * currentShape->scaledDimensions.y;
				}
				else if (totalMovement->y < 0) {
					cameraPosition.y = currentShape->translatedPos.y + 0.5f * currentShape->scaledDimensions.y + DIMENSIONS.y;
					gravitySpeed = START_GRAVITY_SPEED;
					bottomCollision = true;
				}
			}
		}
		*onGround = bottomCollision;
	}
	void Player::manageCollisionZ(glm::vec3 *totalMovement) {
		for (unsigned int i = 0; i < Map::chunks.size(); i++) {
			Chunk *currentChunk = Map::chunks[i];
			int collisionValue = currentChunk->collision(cameraPosition, DIMENSIONS);
			if (collisionValue >= 0) {
				Shape *currentShape = currentChunk->shapes[collisionValue];
				if (totalMovement->z > 0) {
					cameraPosition.z = currentShape->translatedPos.z - 0.5f * currentShape->scaledDimensions.z - 0.5f * DIMENSIONS.z;
				}
				else if (totalMovement->z < 0) {
					cameraPosition.z = currentShape->translatedPos.z + 0.5f * currentShape->scaledDimensions.z + 0.5f * DIMENSIONS.z;
				}
			}
		}
	}

	//Public
	void Player::move(GLFWwindow *window) {
		if (!beganMotion) {
			clock.setPrevious();
			beganMotion = true;
		}

		const float SPEED = 3.5f;
		const float JUMP_SIZE = -0.5f;

		clock.setCurrent();
		float movementSize = clock.getTimeChange() * SPEED;
		clock.setPrevious();

		glm::vec3 movementDirection = glm::vec3(cameraFront.x, 0.0f, cameraFront.z);
		glm::vec3 totalMovement = glm::vec3(0.0f, 0.0f, 0.0f);

		static bool onGround = false;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			totalMovement += movementDirection * movementSize;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			totalMovement -= movementDirection * movementSize;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			totalMovement -= glm::normalize(glm::cross(movementDirection, UP_VECTOR)) * movementSize;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			totalMovement += glm::normalize(glm::cross(movementDirection, UP_VECTOR)) * movementSize;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && onGround) {
			gravitySpeed = JUMP_SIZE;
			onGround = false;
		}
		applyGravity(&totalMovement, movementSize);

		//Normalize X/Z Plane Velocities
		float movementAngle = atan2(totalMovement.z, totalMovement.x);
		float sinTheta = sin(movementAngle);
		float movementMagnitude = (sinTheta != 0) ? (totalMovement.z / sinTheta) : totalMovement.x;
		totalMovement.x *= ((movementMagnitude != 0) ? (movementSize / movementMagnitude) : 0);
		totalMovement.z *= ((movementMagnitude != 0) ? (movementSize / movementMagnitude) : 0);

		cameraPosition.y += totalMovement.y;
		manageCollisionY(&totalMovement, &onGround);

		cameraPosition.x += totalMovement.x;
		manageCollisionX(&totalMovement);

		cameraPosition.z += totalMovement.z;
		manageCollisionZ(&totalMovement);
	}
	void Player::checkReset(GLFWwindow *window) {
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			gravitySpeed = START_GRAVITY_SPEED;
			cameraPosition = glm::vec3(0.0f, START_Y, 0.0f);
		}
	}
	void Player::moveDebug(GLFWwindow *window) {
		Camera::move(window);
	}
}