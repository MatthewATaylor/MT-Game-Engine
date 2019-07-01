#include "Player.h"

namespace mtge {
	//Constructor
	Player::Player(glm::vec3 position, const glm::vec3 DIMENSIONS) : Camera(position, glm::vec3(0.0f, 0.0f, -1.0f)), DIMENSIONS(DIMENSIONS) {}

	//Private
	void Player::manageCollisionX() {
		for (unsigned int i = 0; i < WorldMap::getNumRenderablesSets(); i++) {
			RenderablesSet *currentRenderablesSet = WorldMap::getRenderablesSetPtr(i);
			if (currentRenderablesSet->getIsVisible()) {
				int collisionValue = currentRenderablesSet->checkAllShapeCollisions(position, DIMENSIONS);
				if (collisionValue >= 0) {
					Shape *currentShape = currentRenderablesSet->getShapePtr(collisionValue);
					if (totalMovement.x > 0) {
						position.x = currentShape->translatedPos.x - 0.5f * currentShape->scaledDimensions.x - 0.5f * DIMENSIONS.x;
					}
					else if (totalMovement.x < 0) {
						position.x = currentShape->translatedPos.x + 0.5f * currentShape->scaledDimensions.x + 0.5f * DIMENSIONS.x;
					}
				}
			}
		}
	}
	void Player::manageCollisionY() {
		bool bottomCollision = false;
		for (unsigned int i = 0; i < WorldMap::getNumRenderablesSets(); i++) {
			RenderablesSet *currentRenderablesSet = WorldMap::getRenderablesSetPtr(i);
			if (currentRenderablesSet->getIsVisible()) {
				int collisionValue = currentRenderablesSet->checkAllShapeCollisions(position, DIMENSIONS);
				if (collisionValue >= 0) {
					Shape *currentShape = currentRenderablesSet->getShapePtr(collisionValue);
					if (totalMovement.y > 0) {
						position.y = currentShape->translatedPos.y - 0.5f * currentShape->scaledDimensions.y;
					}
					else if (totalMovement.y < 0) {
						position.y = currentShape->translatedPos.y + 0.5f * currentShape->scaledDimensions.y + DIMENSIONS.y;
						gravitySpeed = startGravitySpeed;
						bottomCollision = true;
					}
				}
			}
		}
		onGround = bottomCollision;
	}
	void Player::manageCollisionZ() {
		for (unsigned int i = 0; i < WorldMap::getNumRenderablesSets(); i++) {
			RenderablesSet *currentRenderablesSet = WorldMap::getRenderablesSetPtr(i);
			if (currentRenderablesSet->getIsVisible()) {
				int collisionValue = currentRenderablesSet->checkAllShapeCollisions(position, DIMENSIONS);
				if (collisionValue >= 0) {
					Shape *currentShape = currentRenderablesSet->getShapePtr(collisionValue);
					if (totalMovement.z > 0) {
						position.z = currentShape->translatedPos.z - 0.5f * currentShape->scaledDimensions.z - 0.5f * DIMENSIONS.z;
					}
					else if (totalMovement.z < 0) {
						position.z = currentShape->translatedPos.z + 0.5f * currentShape->scaledDimensions.z + 0.5f * DIMENSIONS.z;
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

		totalMovement.y -= gravitySpeed * movementSize;
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
	void Player::controlJump(GLFWwindow *window, float jumpSize, int jumpKey) {
		if ((glfwGetKey(window, jumpKey) == GLFW_PRESS) && onGround) {
			gravitySpeed = jumpSize;
			onGround = false;
		}
	}
	void Player::controlMotion(GLFWwindow *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey) {
		glm::vec3 movementDirection = glm::vec3(front.x, 0.0f, front.z);
		controlRawMotion(window, speed, forwardKey, reverseKey, leftKey, rightKey, movementDirection);

		if (canApplyGravity) {
			applyGravity();
		}

		//Normalize X/Z Plane Velocities
		float movementAngle = atan2(totalMovement.z, totalMovement.x);
		float sinTheta = sin(movementAngle);
		float movementMagnitude = (sinTheta != 0) ? (totalMovement.z / sinTheta) : totalMovement.x;
		totalMovement.x *= ((movementMagnitude != 0) ? (movementSize / movementMagnitude) : 0);
		totalMovement.z *= ((movementMagnitude != 0) ? (movementSize / movementMagnitude) : 0);

		if (canApplyCollisions) {
			position.y += totalMovement.y;
			manageCollisionY();

			position.x += totalMovement.x;
			manageCollisionX();

			position.z += totalMovement.z;
			manageCollisionZ();
		}
		else {
			position += totalMovement;
		}
	}
	void Player::controlReset(GLFWwindow *window, float resetHeight) {
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			gravitySpeed = startGravitySpeed;
			position = glm::vec3(0.0f, resetHeight, 0.0f);
		}
	}
}