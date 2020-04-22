#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Clock.h"
#include "Window.h"
#include "ResourceManager.h"
#include "Math/Vec.h"
#include "Math/Mat.h"
#include "Math/Util.h"

namespace mtge {
	class Camera {
	protected:
		const math::Vec3 UP_VECTOR = math::Vec3(0.0f, 1.0f, 0.0f);
		math::Vec3 position;
		math::Vec3 front;
		math::Vec3 totalMovement;
		Clock clock;
		float previousMouseX = 0.0f;
		float previousMouseY = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
		bool firstMouseEntrance = true;
		float fieldOfView = 45.0f;
		float movementSize = 0.0f;
		bool beganMotion = false;

		void controlRawMotion(Window *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey, math::Vec3 movementDirection);

	public:
		Camera(math::Vec3 position, math::Vec3 front);
		virtual void controlMotion(Window *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey);
		void controlRotation(double xPos, double yPos);
		void controlZoom(double xOffset, double yOffset);
		float getFieldOfView();
		float getMovementSize();
		math::Vec3 getPosition();
		math::Mat4 getProjectionMatrix(Window *window);
		virtual math::Mat4 getViewMatrix();
	};
}