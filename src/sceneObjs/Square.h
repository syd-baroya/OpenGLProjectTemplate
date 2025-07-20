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
    Square () { 
        shaderProgram = new ShaderProgram("../resources/default.vert", "../resources/default.frag");

        // Generates Vertex Array Object and binds it
        vao = new VAO();
        vao->bind();

        // Generates Vertex Buffer Object and links it to vertices
        vbo = new VBO(vertices, sizeof(vertices));
        // Generates Element Buffer Object and links it to indices
        ebo = new EBO(indices, sizeof(indices));

        // Links VBO attributes such as coordinates and colors to VAO
        vao->linkAttrib(*vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
        vao->linkAttrib(*vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        vao->linkAttrib(*vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

        // Unbind all to prevent accidentally modifying them
        vao->unbind();
        vbo->unbind();
        ebo->unbind();
    }

    void update() {}

    void render() {
        shaderProgram->bind();

        vao->bind();
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        shaderProgram->unbind();
    }

    void destroy() {
        vao->destroy();
        vbo->destroy();
        ebo->destroy();
        shaderProgram->destroy();
    }

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