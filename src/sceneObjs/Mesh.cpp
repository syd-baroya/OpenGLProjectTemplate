#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	// Generates Vertex Array Object and binds it
	vao = new VAO();
	vao->bind();

	// Generates Vertex Buffer Object and links it to vertices
	vbo = new VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	ebo = new EBO(indices);

	// Links VBO attributes such as coordinates and colors to VAO
	vao->linkAttrib(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao->linkAttrib(*vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vao->linkAttrib(*vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	vao->linkAttrib(*vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	vao->unbind();
	vbo->unbind();
	ebo->unbind();
}


void Mesh::render(ShaderProgram& shader)
{
	vao->bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;
	unsigned int numNormal = 0;
	unsigned int numHeight = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse") {
			num = std::to_string(numDiffuse++);
		} else if (type == "specular") {
			num = std::to_string(numSpecular++);
		} else if (type == "normal") {
			num = std::to_string(numNormal++);
		} else if (type == "height") {
			num = std::to_string(numHeight++);
		}
		shader.setInt((type + num).c_str(), textures[i].unit);
		textures[i].bind();
	}

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::destroy() {
	vao->destroy();
	vbo->destroy();
	ebo->destroy();
}