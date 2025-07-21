#pragma once

#ifndef SQUARE_H
#define SQUARE_H

#include "SceneObject.h"
#include <GLFW/glfw3.h>
#include "../helpers/VAO.h"
#include "../helpers/VBO.h"
#include "../helpers/EBO.h"

class Square : public SceneObject {

public:
    Square();

    void update(float rotation, float aspect, GLuint shaderID);

    void render();

    void destroy();

private:
    VAO* vao;
    VBO* vbo;
    EBO* ebo;

    // Vertices coordinates
    GLfloat vertices[sizeof(GLfloat)*24] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
         0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
         0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
    };

    // Indices for vertices order
    GLuint indices[sizeof(GLuint)*6] =
    {
        0, 2, 1, // Upper triangle
        0, 3, 2 // Lower triangle
    };
};

#endif