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
	VAO* vao;
	VBO* vbo;
	EBO* ebo;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
	// Draws the mesh
	void render(ShaderProgram& shader);

	void destroy();
};

#endif
