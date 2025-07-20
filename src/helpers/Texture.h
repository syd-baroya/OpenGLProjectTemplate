#pragma once
#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include "ShaderProgram.h"

class Texture
{
public:
	GLuint ID;
	const char* type;
	GLuint unit;

	Texture(const char* image, const char* texType, GLuint slot);


	// Assigns a texture unit to a texture
	void assign(ShaderProgram* shader, const char* uniform);
	// Binds a texture
	void bind();
	// Unbinds a texture
	void unbind();
	// Deletes a texture
	void destroy();
};
#endif