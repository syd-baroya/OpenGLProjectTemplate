#include "Mesh.h"

#include <memory>
Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<std::shared_ptr<Texture>>& textures)
: vertices(vertices), indices(indices), textures(textures)
{
	vao = std::make_unique<VAO>();
	vao->bind();

	vbo = std::make_unique<VBO>(vertices);
	ebo = std::make_unique<EBO>(indices);

	vao->linkAttrib(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao->linkAttrib(*vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vao->linkAttrib(*vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	vao->linkAttrib(*vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	vao->unbind();
	vbo->unbind();
	ebo->unbind();
}

void Mesh::render(ShaderProgram& shader)
{
	vao->bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;
	unsigned int numNormal = 0;
	unsigned int numHeight = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i]->type;
		if (type == "diffuse") {
			num = std::to_string(numDiffuse++);
		} else if (type == "specular") {
			num = std::to_string(numSpecular++);
		} else if (type == "normal") {
			num = std::to_string(numNormal++);
		} else if (type == "height") {
			num = std::to_string(numHeight++);
		}
		shader.setInt((type + num).c_str(), textures[i]->unit);
		textures[i]->bind();
	}

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	for (unsigned int j = 0; j < textures.size(); j++)
	{
		textures[j]->unbind();
	}
	vao->unbind();
}