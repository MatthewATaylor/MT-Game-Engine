#include "../Include/Player.h"

namespace mtge {
	//Constructor
	Player::Player(math::Vec<float, 3> position, const math::Vec<float, 3> DIMENSIONS) : 
		Camera(position, math::Vec<float, 3>(0.0f, 0.0f, 1.0f)), DIMENSIONS(DIMENSIONS) {}

	//Private
	void Player::manageCollisionX() {
		for (unsigned int i = 0; i < WorldMap::getNumRenderablesSets(); i++) {
			RenderablesSet *currentRenderablesSet = WorldMap::getRenderablesSetPtr(i);
			if (currentRenderablesSet->getIsVisible()) {
				int collisionValue = currentRenderablesSet->checkAllShapeCollisions(position, DIMENSIONS);
				if (collisionValue >= 0) {
					Shape *currentShape = currentRenderablesSet->getShapePtr(collisionValue);
					if (totalMovement.getX() > 0) {
						position.setX(currentShape->getCenterPosition().x - 0.5f * currentShape->getDimensions().x - 0.5f * DIMENSIONS.getX());
					}
					else if (totalMovement.getX() < 0) {
						position.setX(currentShape->getCenterPosition().x + 0.5f * currentShape->getDimensions().x + 0.5f * DIMENSIONS.getX());
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
					if (totalMovement.getY() > 0) {
						position.setY(currentShape->getCenterPosition().y - 0.5f * currentShape->getDimensions().y - 0.5f * DIMENSIONS.getY());
						gravitySpeed = 0.0f;
					}
					else if (totalMovement.getY() < 0) {
						position.setY(currentShape->getCenterPosition().y + 0.5f * currentShape->getDimensions().y + 0.5f * DIMENSIONS.getY());
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
					if (totalMovement.getZ() > 0) {
						position.setZ(currentShape->getCenterPosition().z - 0.5f * currentShape->getDimensions().z - 0.5f * DIMENSIONS.getZ());
					}
					else if (totalMovement.getZ() < 0) {
						position.setZ(currentShape->getCenterPosition().z + 0.5f * currentShape->getDimensions().z + 0.5f * DIMENSIONS.getZ());
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
	void Player::controlMotion(Window *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey) {
		math::Vec<float, 3> movementDirection = math::Vec<float, 3>(front.getX(), 0.0f, front.getZ());
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
			manageCollisionY();

			position.setX(position.getX() + totalMovement.getX());
			manageCollisionX();

			position.setZ(position.getZ() + totalMovement.getZ());
			manageCollisionZ();
		}
		else {
			position += totalMovement;
		}
	}
	void Player::controlReset(Window *window, float resetHeight) {
		if (glfwGetKey(window->getPtr_GLFW(), GLFW_KEY_R) == GLFW_PRESS) {
			gravitySpeed = startGravitySpeed;
			position = math::Vec<float, 3>(0.0f, resetHeight, 0.0f);
		}
	}
	math::Mat<float, 4, 4> Player::getViewMatrix() {
		math::Vec<float, 3> eye(position.getX(), position.getY() + 0.4f * DIMENSIONS.getY(), position.getZ());
		return math::Util::lookAt(eye, eye + front, UP_VECTOR);
	}
}