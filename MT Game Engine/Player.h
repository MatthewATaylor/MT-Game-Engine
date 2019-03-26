#pragma once

#include <math.h>

#include "Map.h"
#include "Camera.h"

namespace mtge {
	class Player : public Camera {
	private:
		const glm::vec3 DIMENSIONS;
		float startGravitySpeed = 0.0f;
		float gravitySpeed = 0.0f;
		float gravityAddend = 0.0f;
		float maxGravity = 0.0f;
		bool onGround = false;
		bool canApplyCollisions = false;
		bool canApplyGravity = false;

		void manageCollisionX();
		void manageCollisionY();
		void manageCollisionZ();
		void applyGravity();

	public:
		Player(glm::vec3 position, const glm::vec3 DIMENSIONS);
		void setCanApplyCollisions(bool canApplyCollisions);
		void setCanApplyGravity(bool canApplyGravity);
		void setGravityParams(float startGravitySpeed, float gravityAddend, float maxGravity);
		void jump(GLFWwindow *window, float jumpSize, int jumpKey);
		void move(GLFWwindow *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey);
		void checkReset(GLFWwindow *window, float resetHeight);
	};
}