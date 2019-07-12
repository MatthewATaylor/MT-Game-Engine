#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Clock.h"
#include "Window.h"
#include "ResourceManager.h"

namespace mtge {
	class Camera {
	protected:
		const glm::vec3 UP_VECTOR = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 totalMovement;
		Clock clock;
		float previousMouseX = 0.0f;
		float previousMouseY = 0.0f;
		float pitch;
		float yaw;
		bool firstMouseEntrance = true;
		float fieldOfView = 45.0f;
		float movementSize = 0.0f;
		bool beganMotion = false;

		void controlRawMotion(Window *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey, glm::vec3 movementDirection);

	public:
		Camera(glm::vec3 position, glm::vec3 front);
		virtual void controlMotion(Window *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey);
		void controlRotation(double xPos, double yPos);
		void controlZoom(double xOffset, double yOffset);
		float getFieldOfView();
		glm::mat4 getViewMatrix();
		glm::vec3 getPosition();
	};
}