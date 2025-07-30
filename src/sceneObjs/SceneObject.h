#pragma once

#ifndef SCENE_OBJ_H
#define SCENE_OBJ_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../helpers/ShaderProgram.h"

class SceneObject {

public:
	SceneObject() {
		this->position = glm::vec3(0);
		this->orientation = glm::vec3(0);
		this->scale = glm::vec3(1);
	}

	virtual glm::mat4 getModelMatrix() = 0;
	virtual void setPosition(glm::vec3 newPos){
		this->position = newPos;
	}
	virtual void update(double delta) = 0;
	virtual void render(ShaderProgram& shader) = 0;
	virtual void destroy() = 0;

	int id;
	glm::vec3 position;
	glm::vec3 orientation;
	glm::vec3 scale;

	std::string name = "";

};

#endif