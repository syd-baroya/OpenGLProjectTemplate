#include "Camera.h"

Camera::Camera(int width, int height, Projection proj) : zoom(ZOOM) {
	this->position = glm::vec3(0.0f, 0.0f, 3.0f);
	this->forward = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	
	this->screen_width = width;
	this->screen_height = height;

	this->projType = proj;
}

Camera::Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up, int width, int height, Projection proj) : zoom(ZOOM) {
	this->position = position;
	this->forward = forward;
	this->up = up;

	this->screen_width = width;
	this->screen_height = height;

	this->projType = proj;
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(this->position, this->position + this->forward, this->up);
}

glm::mat4 Camera::getProjectionMatrix() {
	if (this->projType == PERSPECTIVE) {
		return glm::perspective(glm::radians(this->zoom), (float)this->screen_width / (float)this->screen_width, NEAR, FAR);
	}
	else if (this->projType == ORTHOGRAPHIC) {
		return glm::ortho(0.0f, this->screen_width, 0.0f, this->screen_height, NEAR, FAR);
	}
	std::cerr << "Incorrect camera type!" << std::endl;
}

void Camera::processMovement(CameraMovement direction, float deltaTime) {
	float velocity = this->move_speed * deltaTime;
	switch (direction) {
		case FORWARD:
			this->moveForward(velocity);
			break;
		case BACKWARD:
			this->moveBackward(velocity);
			break;
		case LEFT:
			this->moveLeft(velocity);
			break;
		case RIGHT:
			this->moveRight(velocity);
			break;
		case UP:
			this->moveUp(velocity);
			break;
		case DOWN:
			this->moveDown(velocity);
			break;
		default:
			break;
	}
}

void Camera::processLook(double mouseX, double mouseY, double deltaTime) {
	// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
// and then "transforms" them into degrees 
	float rotX = this->mouse_sensitivity * (float)(mouseY - (this->screen_height / 2)) / this->screen_height * deltaTime;
	float rotY = this->mouse_sensitivity * (float)(mouseX - (this->screen_width / 2)) / this->screen_width * deltaTime;

	// Calculates upcoming vertical change in the Orientation
	glm::vec3 newOrientation = glm::rotate(this->forward, glm::radians(-rotX), glm::normalize(glm::cross(this->forward, this->up)));

	// Decides whether or not the next vertical Orientation is legal or not
	if (abs(glm::angle(newOrientation, this->up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		this->forward = newOrientation;
	}

	// Rotates the Orientation left and right
	this->forward = glm::rotate(this->forward, glm::radians(-rotY), this->up);

}


void Camera::processZoom(float yOffset) {
	this->zoom -= yOffset;
	if (this->zoom < 1.0f)
		this->zoom = 1.0f;
	if (this->zoom > 45.0f)
		this->zoom = 45.0f;
}

void Camera::moveLeft(float velocity) {
	this->position -= glm::normalize(glm::cross(this->forward, this->up)) * velocity;
}
void Camera::moveRight(float velocity) {
	this->position += glm::normalize(glm::cross(this->forward, this->up)) * velocity;
}
void Camera::moveForward(float velocity) {
	this->position += velocity * this->forward;
}
void Camera::moveBackward(float velocity) {
	this->position -= velocity * this->forward;
}
void Camera::moveUp(float velocity) {
	this->position += velocity * this->up;
}
void Camera::moveDown(float velocity) {
	this->position -= velocity * this->up;
}