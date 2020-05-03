#include "Interaction/Camera.h"

namespace mtge {
	//Constructor
	Camera::Camera(math::Vec3 position, math::Vec3 front) {
		this->position = position;
		this->front = front;
	}

	//Protected
	void Camera::controlRawMotion(Window *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey, math::Vec3 movementDirection) {
		if (!beganMotion) {
			clock.setPrevious();
			beganMotion = true;
		}
		
		clock.setCurrent();
		movementSize = clock.getTimeChange() * speed;
		clock.setPrevious();

		totalMovement = math::Vec3(0.0f, 0.0f, 0.0f);
		
		if (glfwGetKey(window->getPtr_GLFW(), forwardKey) == GLFW_PRESS) {
			totalMovement += movementDirection * movementSize;
		}
		if (glfwGetKey(window->getPtr_GLFW(), reverseKey) == GLFW_PRESS) {
			totalMovement -= movementDirection * movementSize;
		}
		if (glfwGetKey(window->getPtr_GLFW(), leftKey) == GLFW_PRESS) {
			totalMovement -= math::Util::normalized(movementDirection.cross(UP_VECTOR)) * movementSize;
		}
		if (glfwGetKey(window->getPtr_GLFW(), rightKey) == GLFW_PRESS) {
			totalMovement += math::Util::normalized(movementDirection.cross(UP_VECTOR)) * movementSize;
		}
	}

	//Public
	void Camera::controlMotion(Window *window, float speed, int forwardKey, int reverseKey, int leftKey, int rightKey) {
		controlRawMotion(window, speed, forwardKey, reverseKey, leftKey, rightKey, front);
		position += totalMovement;
	}
	void Camera::controlRotation(double xPos, double yPos) {
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

		math::Vec3 facing;
		float pitchRadians = math::Util::toRadians(pitch);
		float yawRadians = math::Util::toRadians(yaw);
		facing.setX(cos(pitchRadians) * cos(yawRadians));
		facing.setY(sin(pitchRadians));
		facing.setZ(cos(pitchRadians) * sin(yawRadians));
		front = math::Util::normalized(facing);

		previousMouseX = (float)xPos;
		previousMouseY = (float)yPos;
	}
	void Camera::controlZoom(double xOffset, double yOffset) {
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
	float Camera::getMovementSize() {
		return movementSize;
	}
	math::Vec3 Camera::getPosition() {
		return position;
	}
	math::Vec3 Camera::getFront() {
		return front;
	}
	math::Mat4 Camera::getProjectionMatrix(Window *window) {
		return math::Util::MatGen::perspective<float>(math::Util::toRadians(fieldOfView), (float)window->getWidth(), (float)window->getHeight(), 0.01f, 100.0f);
	}
	math::Mat4 Camera::getViewMatrix() {
		math::Mat4 viewMatrix = math::Util::MatGen::lookAt(position, position + front, UP_VECTOR);
		return viewMatrix;
	}
}