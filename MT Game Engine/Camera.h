#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Clock.h"
#include "GlobalConstants.h"

namespace mtge {
	class Camera {
	protected:
		const glm::vec3 UP_VECTOR = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraPosition;
		glm::vec3 cameraFront;
		Clock clock;
		float previousMouseX = (float)SCREEN_WIDTH / 2.0f;
		float previousMouseY = (float)SCREEN_HEIGHT / 2.0f;
		float pitch;
		float yaw;
		bool firstMouseEntrance = true;
		float fieldOfView = 45.0f;

	public:
		Camera(glm::vec3 cameraPosition, glm::vec3 cameraFront);
		virtual void move(GLFWwindow *window);
		void rotate(GLFWwindow *window, double xPos, double yPos);
		void zoom(GLFWwindow *window, double xOffset, double yOffset);
		float getFieldOfView();
		glm::mat4 viewMatrix();
		glm::vec3 getCameraPosition();
	};
}