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
#include "Rendering/Texture/CubeTexture.h"
#include "Rendering/RenderedCube.h"

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
		Chunk *currentChunk = nullptr;
		math::Vec<unsigned int, 3> positionIndices;
		unsigned int playerHeightInCubes;
		unsigned int jumpHeightInCubes = 0;

		math::Vec3 getCubePosFromIndices(const math::Vec<unsigned int, 3> &indices, Chunk *chunk);

		void setBottomCollisionCoordsToCheck();
		void setTopCollisionCoordsToCheck();
		void setFrontCollisionCoordsToCheck();
		void setBackCollisionCoordsToCheck();
		void setLeftCollisionCoordsToCheck();
		void setRightCollisionCoordsToCheck();
		void setFrontRightCollisionCoordsToCheck();
		void setBackRightCollisionCoordsToCheck();
		void setFrontLeftCollisionCoordsToCheck();
		void setBackLeftCollisionCoordsToCheck();

		void setCollisionCoordsToCheck();

		bool isCubeCollision(math::Vec3 cubePos, math::Vec3 cubeDimens);
		void manageCollisionX();
		void manageCollisionY();
		void manageCollisionZ();

		void applyGravity();
		void reduceMotion();

		void setCurrentChunk();
		void setPositionIndices();

	public:
		Player(math::Vec3 position, const math::Vec3 DIMENSIONS);
		void setCanApplyCollisions(bool canApplyCollisions);
		void setCanApplyGravity(bool canApplyGravity);
		void setGravityParams(float startGravitySpeed, float gravityAddend, float maxGravity);
		void controlJump(Window *window, float jumpSize, int jumpKey);
		void controlMotion(Window *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey);
		void controlReset(Window *window, float resetHeight);
		math::Vec3 getPosition();
		Chunk *getCurrentChunk();
		math::Mat4 getViewMatrix() override;
	};
}

