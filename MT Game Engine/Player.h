#pragma once

#include <math.h>

#include "Map.h"
#include "Camera.h"
#include "GlobalConstants.h"

namespace mtge {
	class Player : public Camera {
	private:
		const glm::vec3 DIMENSIONS;
		const float START_GRAVITY_SPEED = 0.01f;
		float gravitySpeed = START_GRAVITY_SPEED;
		bool beganMotion = false;

		void applyGravity(glm::vec3 *totalMovement, float movementSize);
		void manageCollisionX(glm::vec3 *totalMovement);
		void manageCollisionY(glm::vec3 *totalMovement, bool *onGround);
		void manageCollisionZ(glm::vec3 *totalMovement);

	public:
		Player(glm::vec3 position, const glm::vec3 DIMENSIONS);
		void move(GLFWwindow *window);
		void checkReset(GLFWwindow *window);
		void moveDebug(GLFWwindow *window);
	};
}