#pragma once

#ifndef CUBE_H
#define CUBE_H

#include "SceneObject.h"
#include <GLFW/glfw3.h>
#include "../helpers/VAO.h"
#include "../helpers/VBO.h"
#include "../helpers/EBO.h"

class Cube : public SceneObject {

public:
    Cube();

    glm::mat4 getModelMatrix();

    void update(double delta);

    void render();

    void destroy();

private:
    VAO* vao;
    VBO* vbo;
    EBO* ebo;

    // Vertices coordinates
    GLfloat vertices[sizeof(GLfloat) * 24] =
    { //     COORDINATES     //
     -0.1f, -0.1f,  0.1f,
     -0.1f, -0.1f, -0.1f,
      0.1f, -0.1f, -0.1f,
      0.1f, -0.1f,  0.1f,
     -0.1f,  0.1f,  0.1f,
     -0.1f,  0.1f, -0.1f,
      0.1f,  0.1f, -0.1f,
      0.1f,  0.1f,  0.1f
    };

    // Indices for vertices order
    GLuint indices[sizeof(GLuint) * 36] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7
    };

};

#endif