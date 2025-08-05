#ifndef MESH_H
#define MESH_H

#include <string>

#include "../helpers/VAO.h"
#include "../helpers/EBO.h"
#include "../helpers/Texture.h"

class Mesh {

public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	// Store VAO in public so it can be used in the Draw function
	std::unique_ptr<VAO> vao;
	std::unique_ptr<VBO> vbo;
	std::unique_ptr<EBO> ebo;

	// Initializes the mesh
	Mesh(const std::vector <Vertex>& vertices, const std::vector <GLuint>& indices, const std::vector <Texture>& textures);
	// Draws the mesh
	void render(ShaderProgram& shader);

	void destroy();
};

#endif
