#pragma once
#pragma once

#ifndef PYRAMID_H
#define PYRAMID_H

#include "SceneObject.h"
#include <GLFW/glfw3.h>
#include "../helpers/VAO.h"
#include "../helpers/VBO.h"
#include "../helpers/EBO.h"

class Pyramid : public SceneObject {

public:
    Pyramid();

    void update(float rotation, float aspect, GLuint shaderID);

    void render();

    void destroy();

private:
    VAO* vao;
    VBO* vbo;
    EBO* ebo;

    // Vertices coordinates
    GLfloat vertices[sizeof(GLfloat) * 40] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, 0.0f,  0.5f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     0.0f, 1.0f, 0.0f,	5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     0.5f, 0.0f, 0.5f,	5.0f, 0.0f,
     0.0f, 0.8f,  0.0f,     1.0f, 1.0f, 1.0f,	2.5f, 5.0f
    };

    // Indices for vertices order
    GLuint indices[sizeof(GLuint) * 18] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };
};

#endif