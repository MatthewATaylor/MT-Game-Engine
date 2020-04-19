#pragma once

#include <vector>
#include <cmath>

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
		std::vector<math::Vec3> collisionCoordsToCheck;
		math::Vec<int, 2> prevChunkIndices;
		unsigned int mapChunkIndex = 0;
		unsigned int playerHeightInCubes;
		unsigned int jumpHeightInCubes = 0;

		math::Vec3 getCubePosFromIndices(math::Vec<unsigned int, 3> indices, unsigned int chunkIndex);

		void setBottomCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices);
		void setTopCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices);
		void setFrontCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices);
		void setBackCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices);
		void setLeftCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices);
		void setRightCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices);
		void setFrontRightCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices);
		void setBackRightCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices);
		void setFrontLeftCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices);
		void setBackLeftCollisionCoordsToCheck(const math::Vec<unsigned int, 3> &posIndices);

		void setCollisionCoordsToCheck();

		bool isCubeCollision(math::Vec3 cubePos, math::Vec3 cubeDimens);
		void manageCollisionX();
		void manageCollisionY();
		void manageCollisionZ();

		void applyGravity();

		math::Vec<int, 2> getChunkPositionIndices();
		math::Vec<unsigned int, 3> getPositionIndices();
		void setMapChunkIndex();

	public:
		Player(math::Vec3 position, const math::Vec3 DIMENSIONS);
		void setCanApplyCollisions(bool canApplyCollisions);
		void setCanApplyGravity(bool canApplyGravity);
		void setGravityParams(float startGravitySpeed, float gravityAddend, float maxGravity);
		void controlJump(Window *window, float jumpSize, int jumpKey);
		void controlMotion(Window *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey);
		void controlReset(Window *window, float resetHeight);
		math::Mat4 getViewMatrix() override;
	};
}

