#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include <filesystem>
#include <iostream>
#include <map>
#include "WindowManager.h"
#include "sceneObjs/Square.h"
#include "sceneObjs/Pyramid.h"
#include "sceneObjs/Cube.h"
#include "helpers/Texture.h"
#include "helpers/Camera.h"
#include <glm/glm.hpp>
#include "sceneObjs/Otter.h"

namespace fs = std::filesystem;

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

class Application : public EventCallbacks {
public:
    Application(unsigned int width, unsigned int height);
    void init();
    void initTextures();
    void initShaders();
    void initObjects();
    void update();
    void render();
    void destroy();

    // inherited functions
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
    void mouseCallback(GLFWwindow* window, int button, int action, int mods) override;
    void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) override;
    void scrollCallback(GLFWwindow* window, double dX, double dY) override;
    void resizeCallback(GLFWwindow* window, int in_width, int in_height) override;

private:
    Time time;
    Camera camera;

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);

	SceneObject* square;
	SceneObject* pyramid;
	SceneObject* lightCube;
	SceneObject* otter;

	ShaderProgram* phongShader;
	ShaderProgram* lightShader;
	ShaderProgram* defaultShader;

    std::shared_ptr<Texture> woodTexture;
    std::shared_ptr<Texture> happyTexture;

	//std::map<std::string, Texture*> textures;

    std::string texturesDir = "../resources/images/";
    std::string shadersDir = "../resources/shaders/";
    std::string modelsDir = "../resources/models/";

    unsigned int width, height;
    bool mouseClicked = true;
    bool mouseMoving = false;
    float lastX;
    float lastY;
    bool holdingDownKey = false;
};

#endif
	