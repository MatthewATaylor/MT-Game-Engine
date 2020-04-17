#pragma once

#include "Camera.h"
#include "Window.h"
#include "ResourceManager.h"
#include "Math/Vec.h"
#include "Math/Mat.h"
#include "Math/Util.h"

namespace mtge {
	class Player : public Camera {
	private:
		const math::Vec<float, 3> DIMENSIONS;
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
		Player(math::Vec<float, 3> position, const math::Vec<float, 3> DIMENSIONS);
		void setCanApplyCollisions(bool canApplyCollisions);
		void setCanApplyGravity(bool canApplyGravity);
		void setGravityParams(float startGravitySpeed, float gravityAddend, float maxGravity);
		void controlJump(Window *window, float jumpSize, int jumpKey);
		void controlMotion(Window *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey) override;
		void controlReset(Window *window, float resetHeight);
		math::Mat<float, 4, 4> getViewMatrix() override;
	};
}

