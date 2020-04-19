#pragma once

#include "Camera.h"
#include "Window.h"
#include "ResourceManager.h"
#include "Math/Vec.h"
#include "Math/Mat.h"
#include "Math/Util.h"
#include "WorldMap.h"
#include "Rendering/Chunk.h"

namespace mtge {
	class Player : public Camera {
	private:
		const math::Vec3 DIMENSIONS;
		float startGravitySpeed = 0.0f;
		float gravitySpeed = 0.0f;
		float gravityAddend = 0.0f;
		float maxGravity = 0.0f;
		bool onGround = false;
		bool canApplyCollisions = false;
		bool canApplyGravity = false;

		bool isCubeCollision(math::Vec3 cubePos, math::Vec3 cubeDimens);
		void manageCollisionX(WorldMap *worldMap);
		void manageCollisionY(WorldMap *worldMap);
		void manageCollisionZ(WorldMap *worldMap);
		void applyGravity();
		math::Vec<int, 2> getChunkPositionIndices();
		math::Vec<int, 3> getPositionIndices();

	public:
		Player(math::Vec3 position, const math::Vec3 DIMENSIONS);
		void setCanApplyCollisions(bool canApplyCollisions);
		void setCanApplyGravity(bool canApplyGravity);
		void setGravityParams(float startGravitySpeed, float gravityAddend, float maxGravity);
		void controlJump(Window *window, float jumpSize, int jumpKey);
		void controlMotion(Window *window, WorldMap *worldMap, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey);
		void controlReset(Window *window, float resetHeight);
		math::Mat4 getViewMatrix() override;
	};
}

