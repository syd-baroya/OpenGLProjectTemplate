#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include<filesystem>
namespace fs = std::filesystem;
#include <iostream>
#include "WindowManager.h"
#include "sceneObjs/Square.h"
#include "sceneObjs/Pyramid.h"
#include "sceneObjs/Cube.h"
#include "helpers/Texture.h"
#include "helpers/Camera.h"	
#include <glm/glm.hpp>
#include "sceneObjs/Model.h"


class Time {
	public:
		Time();
		void update();
		double getDelta();

	private:
		double prevTime;
		double deltaTime;
		double currTime;
};

class Application : public EventCallbacks
{

	public:
		void init(unsigned int width, unsigned int height);
		void initTextures();
		void initShaders();
		void initObjects();
		void update();
		void render();
		void destroy();

		//inherited functions
		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		void mouseCallback(GLFWwindow* window, int button, int action, int mods);

		void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);

		void scrollCallback(GLFWwindow* window, double dX, double dY);

		void resizeCallback(GLFWwindow* window, int in_width, int in_height);

private:
	Time* time;
	Camera* camera;

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);

	SceneObject* square;
	SceneObject* pyramid;
	SceneObject* lightCube;

	Model* backpack;

	ShaderProgram* defaultShader;
	ShaderProgram* lightShader;
	ShaderProgram* backpackShader;

	std::vector<Texture> textures;

	std::string texturesDir = "../resources/images/";
	std::string shadersDir = "../resources/shaders/";
	std::string modelsDir = "../resources/models/";

	unsigned int width, height;
	bool mouseClicked = true;
	bool mouseMoving = false;
	float lastX;
	float lastY;
	float holdingDownKey = false;
};

#endif
	