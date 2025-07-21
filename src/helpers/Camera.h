#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LOOK_UP,
	LOOK_DOWN,
	LOOK_LEFT,
	LOOK_RIGHT,
};

enum Projection {
	ORTHOGRAPHIC,
	PERSPECTIVE
};

const glm::vec3 WORLD_UP(0.0f, 1.0f, 0.0f);

const float NEAR = 0.1f;
const float FAR = 100.0f;
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ZOOM = 45.0f;

class Camera {
	public:
		Camera(int width, int height, Projection proj = PERSPECTIVE);
		Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up, int width, int height, Projection proj = PERSPECTIVE);

		void processMovement(CameraMovement direction, float deltaTime);
		void processLook(CameraMovement direction, float deltaTime);
		void processLook(float xoffset, float yoffset, float deltaTime);
		void processZoom(float yOffset);

		void moveLeft(float velocity);
		void moveRight(float velocity);
		void moveForward(float velocity);
		void moveBackward(float velocity);
		void moveUp(float velocity);
		void moveDown(float velocity);

		void lookUp(float velocity);
		void lookDown(float velocity);
		void lookLeft(float velocity);
		void lookRight(float velocity);

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();

	private:
		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;
		Projection projType;
		float screen_width;
		float screen_height;
		float pitch;
		float yaw;
		float zoom;
		float move_speed = 2.0f;
		float look_speed = 20.0f;
		float mouse_sensitivity = 0.1f;
		void updateCameraVectors();
};

#endif
