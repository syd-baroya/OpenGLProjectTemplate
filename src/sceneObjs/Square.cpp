#include "Square.h"

Square::Square() {
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

void Square::update() {}

void Square::render() {
    vao->bind();
    // Draw primitives, number of indices, datatype of indices, index of indices
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}

void Square::destroy() {
    vao->destroy();
    vbo->destroy();
    ebo->destroy();
}