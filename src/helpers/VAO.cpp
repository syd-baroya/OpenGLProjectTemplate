#include"VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO Attribute such as a position or color to the VAO
void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset)
{
	VBO.bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.unbind();
}


// Binds the VAO
void VAO::bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::destroy()
{
	glDeleteVertexArrays(1, &ID);
}