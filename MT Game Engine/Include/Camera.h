#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Clock.h"
#include "Window.h"
#include "ResourceManager.h"
#include "Math/Vec.h"
#include "Math/Mat.h"
#include "Math/Util.h"

namespace mtge {
	class Camera {
	protected:
		const math::Vec<float, 3> UP_VECTOR = math::Vec<float, 3>(0.0f, 1.0f, 0.0f);
		math::Vec<float, 3> position;
		math::Vec<float, 3> front;
		math::Vec<float, 3> totalMovement;
		Clock clock;
		float previousMouseX = 0.0f;
		float previousMouseY = 0.0f;
		float pitch;
		float yaw;
		bool firstMouseEntrance = true;
		float fieldOfView = 45.0f;
		float movementSize = 0.0f;
		bool beganMotion = false;

		void controlRawMotion(Window *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey, math::Vec<float, 3> movementDirection);

	public:
		Camera(math::Vec<float, 3> position, math::Vec<float, 3> front);
		virtual void controlMotion(Window *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey);
		void controlRotation(double xPos, double yPos);
		void controlZoom(double xOffset, double yOffset);
		float getFieldOfView();
		math::Vec<float, 3> getPosition();
		virtual glm::mat4 getViewMatrix();
	};
}