#pragma once
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const std::string &filename);

class ShaderProgram {
	public:
		// Reference ID of the Shader Program
		GLuint ID;
		// Constructor that build the Shader Program from 2 different shaders
		ShaderProgram(const std::string& vertexFile, const std::string& fragmentFile);

		void setBool(const char* name, bool value);
		void setInt(const char *name, int value);
		void setFloat(const char *name, float value);
		void setVec2(const char* name, float x, float y);
		void setVec2(const char* name, const glm::vec2& value);
		void setVec3(const char* name, float x, float y, float z);
		void setVec3(const char* name, const glm::vec3& value);
		void setVec4(const char* name, float x, float y, float z, float w);
		void setVec4(const char* name, const glm::vec4& value);
		void setMat4(const char *name, glm::mat4 value);

		void bind();
		void unbind();
		GLuint createShader(const std::string& path, GLenum shaderType);

		// Deletes the Shader Program
		void destroy();
		~ShaderProgram();

	protected:
		std::string vShaderName;
		std::string fShaderName;

	private:
		// Checks if the different Shaders have compiled properly
		void compileErrors(unsigned int shader, const char* type);
		std::string getShaderTypeAsString(GLenum shaderType);
};

#endif
