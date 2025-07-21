#include "Camera.h"

Camera::Camera(int width, int height, Projection proj) : yaw(YAW), pitch(PITCH), zoom(ZOOM) {
	this->position = glm::vec3(0.0f, 0.0f, 3.0f);
	this->forward = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	
	this->screen_width = width;
	this->screen_height = height;

	this->projType = proj;
	this->updateCameraVectors();
}

Camera::Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up, int width, int height, Projection proj) : yaw(YAW), pitch(PITCH), zoom(ZOOM) {
	this->position = position;
	this->forward = forward;
	this->up = up;

	this->screen_width = width;
	this->screen_height = height;

	this->projType = proj;
	this->updateCameraVectors();
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

void Camera::processLook(CameraMovement direction, float deltaTime) {
	float velocity = this->look_speed * deltaTime;
	switch (direction) {
		case LOOK_UP:
			this->lookUp(velocity);
			break;
		case LOOK_DOWN:
			this->lookDown(velocity);
			break;
		case LOOK_LEFT:
			this->lookLeft(velocity);
			break;
		case LOOK_RIGHT:
			this->lookRight(velocity);
			break;
		default:
			break;
	}
	this->updateCameraVectors();
}

void Camera::processLook(float xoffset, float yoffset, float deltaTime) {
	xoffset *= this->mouse_sensitivity;
	yoffset *= this->mouse_sensitivity;

	this->yaw += xoffset;
	this->pitch += yoffset;

	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;
	// update Front, Right and Up Vectors using the updated Euler angles
	this->updateCameraVectors();
}


void Camera::processZoom(float yOffset) {
	this->zoom -= yOffset;
	if (this->zoom < 1.0f)
		this->zoom = 1.0f;
	if (this->zoom > 45.0f)
		this->zoom = 45.0f;
}

void Camera::lookUp(float velocity) {
	this->pitch += velocity;
	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
}
void Camera::lookDown(float velocity) {
	this->pitch -= velocity;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;
}
void Camera::lookLeft(float velocity) {
	this->yaw -= velocity;
}
void Camera::lookRight(float velocity) {
	this->yaw += velocity;
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

void Camera::updateCameraVectors() {
	// calculate the new forward vector
	glm::vec3 forward;
	forward.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	forward.y = sin(glm::radians(this->pitch));
	forward.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->forward = glm::normalize(forward);
	// also re-calculate the Right and Up vector
	this->right = glm::normalize(glm::cross(this->forward, WORLD_UP));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->up = glm::normalize(glm::cross(this->right, this->forward));
}