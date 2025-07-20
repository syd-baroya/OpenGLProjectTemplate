#pragma once

#ifndef SCENE_OBJ_H
#define SCENE_OBJ_H

#include <glm/glm.hpp>
#include <iostream>
#include "../helpers/Shader.h"

class SceneObject {

public:
	SceneObject() {}

	virtual void update() = 0;
	virtual void render() = 0;
	virtual void destroy() = 0;

	int id;
	glm::vec3 position;
	glm::vec3 orientation;
	glm::vec3 scale;

	std::string name = "";

	Shader* shaderProgram;
};

#endif