#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "WindowManager.h"
#include "sceneObjs/Square.h"

class Application : public EventCallbacks
{

	public:
		void init();
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
	SceneObject* square;

	ShaderProgram* defaultShader;

};

#endif
	