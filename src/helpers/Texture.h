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
	const char* path;
	GLuint unit;

	Texture() {};

	Texture(const char* image, const char* texType, GLuint slot);
	~Texture();

	// Binds a texture
	void bind();
	// Unbinds a texture
	void unbind();
	// Deletes a texture
	void destroy();
};
#endif