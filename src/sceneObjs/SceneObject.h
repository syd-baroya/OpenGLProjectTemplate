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
		this->id = 0;
		this->name = "scene object";
		this->position = glm::vec3(0);
		this->orientation = glm::vec3(0);
		this->scale = glm::vec3(1);
	}

	virtual glm::mat4 getModelMatrix() {
		return  glm::translate(
					glm::rotate(
						glm::rotate(
							glm::rotate(
								glm::scale(glm::mat4(1.0f), this->scale),
							glm::radians(this->orientation.z), glm::vec3(0.0f, 0.0f, 1.0f)),
						glm::radians(this->orientation.y), glm::vec3(0.0f, 1.0f, 0.0f)),
					glm::radians(this->orientation.x), glm::vec3(1.0f, 0.0f, 0.0f)), 
				this->position);
			
	};
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

	std::string name;

};

#endif