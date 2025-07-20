#include "Shader.h"

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
Shader::Shader(const std::string &vertexFile, const std::string &fragmentFile)
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

GLuint Shader::createShader(const std::string& path, GLenum shaderType) {
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

// Activates the Shader Program
void Shader::bind()
{
	glUseProgram(ID);
}

void Shader::unbind()
{
	glUseProgram(0);
}

// Deletes the Shader Program
void Shader::destroy()
{
	glDeleteProgram(ID);
}

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
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

std::string Shader::getShaderTypeAsString(GLenum shaderType) {
	std::string result;

	switch (shaderType) {
		case GL_VERTEX_SHADER:
			result = "VERTEX";
		case GL_FRAGMENT_SHADER:
			result = "FRAGMENT";
		case GL_GEOMETRY_SHADER:
			result = "GEOMETRY";
		/*case GL_COMPUTE_SHADER:
			result = "COMPUTE";*/ // only works with OpenGL 4.3 and higher
		default:
			result = "";
	}
	return result;
}