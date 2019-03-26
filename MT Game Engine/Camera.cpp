#include "Camera.h"

namespace mtge {
	//Constructor
	Camera::Camera(glm::vec3 position, glm::vec3 front) {
		this->position = position;
		this->front = front;
	}

	//Protected
	void Camera::controlMotion(GLFWwindow *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey, glm::vec3 movementDirection) {
		if (!beganMotion) {
			clock.setPrevious();
			beganMotion = true;
		}
		
		clock.setCurrent();
		movementSize = clock.getTimeChange() * speed;
		clock.setPrevious();

		totalMovement = glm::vec3(0.0f, 0.0f, 0.0f);

		if (glfwGetKey(window, forwardKey) == GLFW_PRESS) {
			totalMovement += movementDirection * movementSize;
		}
		if (glfwGetKey(window, reverseKey) == GLFW_PRESS) {
			totalMovement -= movementDirection * movementSize;
		}
		if (glfwGetKey(window, leftKey) == GLFW_PRESS) {
			totalMovement -= glm::normalize(glm::cross(movementDirection, UP_VECTOR)) * movementSize;
		}
		if (glfwGetKey(window, rightKey) == GLFW_PRESS) {
			totalMovement += glm::normalize(glm::cross(movementDirection, UP_VECTOR)) * movementSize;
		}
	}

	//Public
	void Camera::move(GLFWwindow *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey) {
		controlMotion(window, speed, forwardKey, reverseKey, leftKey, rightKey, front);

		position += totalMovement;
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
		front = glm::normalize(facing);

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
	glm::mat4 Camera::getViewMatrix() {
		return glm::lookAt(position, position + front, UP_VECTOR);
	}
	glm::vec3 Camera::getPosition() {
		return position;
	}
}