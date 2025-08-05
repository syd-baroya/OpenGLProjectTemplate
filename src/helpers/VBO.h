#pragma once
#ifndef VBO_H
#define VBO_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>

//#define MAX_BONE_INFLUENCE 4

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
	//glm::vec3 tangent;
	//glm::vec3 bitangent;
	////bone indexes which will influence this vertex
	//int m_BoneIDs[MAX_BONE_INFLUENCE];
	////weights from each bone
	//float m_Weights[MAX_BONE_INFLUENCE];
};

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(const std::vector<Vertex>& vertices);
	~VBO();
	VBO();
	// Binds the VBO
	void bind();
	// Unbinds the VBO
	void unbind();
	// Deletes the VBO
	void destroy();
};

#endif