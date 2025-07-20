#pragma once
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const std::string &filename);

class Shader {
	public:
		// Reference ID of the Shader Program
		GLuint ID;
		// Constructor that build the Shader Program from 2 different shaders
		Shader(const std::string& vertexFile, const std::string& fragmentFile);

		void bind();
		void unbind();
		GLuint createShader(const std::string& path, GLenum shaderType);

		// Deletes the Shader Program
		void destroy();

	protected:
		std::string vShaderName;
		std::string fShaderName;

	private:
		// Checks if the different Shaders have compiled properly
		void compileErrors(unsigned int shader, const char* type);
		std::string getShaderTypeAsString(GLenum shaderType);
};

#endif
