#include "Camera.h"

namespace mtge {
	//Constructor
	Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraFront) {
		this->cameraPosition = cameraPosition;
		this->cameraFront = cameraFront;
	}

	//Public
	void Camera::move(GLFWwindow *window) {
		const float SPEED = 3.5f;

		clock.setCurrent();
		float movementSize = clock.getTimeChange() * SPEED;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			cameraPosition += cameraFront * movementSize;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			cameraPosition -= cameraFront * movementSize;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			cameraPosition -= glm::normalize(glm::cross(cameraFront, UP_VECTOR)) * movementSize;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			cameraPosition += glm::normalize(glm::cross(cameraFront, UP_VECTOR)) * movementSize;
		}
		clock.setPrevious();
	}
	void Camera::rotate(GLFWwindow *window, double xPos, double yPos) {
		const float MOUSE_SENSITIVITY = 0.05f;

		if (firstMouseEntrance) {
			previousMouseX = (float)xPos;
			previousMouseY = (float)yPos;
			firstMouseEntrance = false;
		}

		float mouseXChange = (float)xPos - previousMouseX;
		float mouseYChange = (float)yPos - previousMouseY;

		yaw += mouseXChange * MOUSE_SENSITIVITY;
		pitch -= mouseYChange * MOUSE_SENSITIVITY;

		if (pitch > 89.0f) {
			pitch = 89.0f;
		}
		else if (pitch < -89.0f) {
			pitch = -89.0f;
		}

		glm::vec3 facing;
		facing.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		facing.y = sin(glm::radians(pitch));
		facing.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		cameraFront = glm::normalize(facing);

		previousMouseX = (float)xPos;
		previousMouseY = (float)yPos;
	}
	void Camera::zoom(GLFWwindow *window, double xOffset, double yOffset) {
		const float SCROLL_SENSITIVITY = 0.7f;
		const float MAX_FOV = 45.0f;

		if (fieldOfView >= 1.0f && fieldOfView <= MAX_FOV) {
			fieldOfView -= (float)yOffset * SCROLL_SENSITIVITY;
		}
		if (fieldOfView <= 1.0f) {
			fieldOfView = 1.0f;
		}
		if (fieldOfView >= MAX_FOV) {
			fieldOfView = MAX_FOV;

		}
	}
	float Camera::getFieldOfView() {
		return fieldOfView;
	}
	glm::mat4 Camera::viewMatrix() {
		return glm::lookAt(cameraPosition, cameraPosition + cameraFront, UP_VECTOR);
	}
	glm::vec3 Camera::getCameraPosition() {
		return cameraPosition;
	}
}