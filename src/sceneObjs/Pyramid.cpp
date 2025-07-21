#include "Pyramid.h"

Pyramid::Pyramid() {

    this->rotation = 0.0f;

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

glm::mat4 Pyramid::getModelMatrix() {
    return glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Pyramid::update(double delta) {
    this->rotation += delta*10.0;
}

void Pyramid::render() {
    vao->bind();
    // Draw primitives, number of indices, datatype of indices, index of indices
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void Pyramid::destroy() {
    vao->destroy();
    vbo->destroy();
    ebo->destroy();
}