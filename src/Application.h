#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include<filesystem>
namespace fs = std::filesystem;

#include "WindowManager.h"
#include "sceneObjs/Square.h"
#include "sceneObjs/Pyramid.h"
#include "helpers/Texture.h"
#include "helpers/Camera.h"	
#include <glm/glm.hpp>


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

	SceneObject* square;
	SceneObject* pyramid;

	ShaderProgram* pyramidShader;

	Texture* woodTexture;
	Texture* happyFaceTexture;

	std::string texturesDir = "../resources/images/";
	std::string shadersDir = "../resources/shaders/";

	unsigned int width, height;
	bool firstMouse = true;
	float lastX;
	float lastY;
};

#endif
	