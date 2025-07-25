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

    glm::mat4 getModelMatrix();
    void update(double delta);

    void render();

    void destroy();

private:
    VAO* vao;
    VBO* vbo;
    EBO* ebo;

    // Vertices coordinates
    GLfloat vertices[sizeof(GLfloat)*24] =
    { //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
        -1.0f, 0.0f,  1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, -1.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
         1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
         1.0f, 0.0f,  1.0f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
    };

    // Indices for vertices order
    GLuint indices[sizeof(GLuint)*6] =
    {
        0, 1, 2,
        0, 2, 3
    };
};

#endif