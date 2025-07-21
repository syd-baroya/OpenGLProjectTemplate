#include "ShaderProgram.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const std::string &filename)
{
	std::string contents;
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
	} else {
		std::cerr << "Could not open file: '" << filename << "'" << std::endl;
	}
	return contents;
}

// Constructor that build the Shader Program from 2 different shaders
ShaderProgram::ShaderProgram(const std::string &vertexFile, const std::string &fragmentFile)
{
	vShaderName = vertexFile;
	fShaderName = fragmentFile;

	GLuint vertexShader = createShader(vertexFile, GL_VERTEX_SHADER);
	GLuint fragmentShader = createShader(fragmentFile, GL_FRAGMENT_SHADER);

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	// Checks if Shaders linked succesfully
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint ShaderProgram::createShader(const std::string& path, GLenum shaderType) {
	// Read vertexFile and fragmentFile and store the strings
	std::string shaderCode = get_file_contents(path);

	// Convert the shader source strings into character arrays
	const char* shaderSource = shaderCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint shader = glCreateShader(shaderType);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(shader, 1, &shaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(shader);
	// Checks if Shader compiled succesfully
	compileErrors(shader, getShaderTypeAsString(shaderType).c_str());

	return shader;
}

void ShaderProgram::setBool(const char* name, bool value) {
	glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void ShaderProgram::setInt(const char* name, int value) {
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void ShaderProgram::setFloat(const char* name, float value) {
	glUniform1f(glGetUniformLocation(ID, name), value);
}

void ShaderProgram::setVec2(const char* name, float x, float y) {
	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void ShaderProgram::setVec3(const char* name, const glm::vec2& value) {
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void ShaderProgram::setVec3(const char* name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void ShaderProgram::setVec3(const char* name, const glm::vec3& value) {
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void ShaderProgram::setMat4(const char* name, glm::mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(value));
}

// Activates the Shader Program
void ShaderProgram::bind()
{
	glUseProgram(ID);
}

void ShaderProgram::unbind()
{
	glUseProgram(0);
}

// Deletes the Shader Program
void ShaderProgram::destroy()
{
	glDeleteProgram(ID);
}

// Checks if the different Shaders have compiled properly
void ShaderProgram::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (strcmp(type, "PROGRAM") != 0)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}

std::string ShaderProgram::getShaderTypeAsString(GLenum shaderType) {
	std::string result;

	switch (shaderType) {
		case GL_VERTEX_SHADER:
			result = "VERTEX";
			break;
		case GL_FRAGMENT_SHADER:
			result = "FRAGMENT";
			break;
		case GL_GEOMETRY_SHADER:
			result = "GEOMETRY";
			break;
		/*case GL_COMPUTE_SHADER:
			result = "COMPUTE";*/ // only works with OpenGL 4.3 and higher
		default:
			result = "";
			break;
	}
	return result;
}