#include "VBO.h"

VBO::VBO()
{
	glGenBuffers(1, &ID);
}
VBO::~VBO() {
	destroy();
}

// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(const std::vector<Vertex>& vertices)
{
	glGenBuffers(1, &ID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

// Binds the VBO
void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::destroy()
{
	glDeleteBuffers(1, &ID);
}