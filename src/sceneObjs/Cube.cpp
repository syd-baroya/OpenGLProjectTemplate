#include "Cube.h"

Cube::Cube() {
    // Generates Vertex Array Object and binds it
    vao = new VAO();
    vao->bind();

    // Generates Vertex Buffer Object and links it to vertices
    vbo = new VBO(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    ebo = new EBO(indices, sizeof(indices));

    // Links VBO attributes such as coordinates and colors to VAO
    vao->linkAttrib(*vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    // Unbind all to prevent accidentally modifying them
    vao->unbind();
    vbo->unbind();
    ebo->unbind();
}

glm::mat4 Cube::getModelMatrix() {
    return glm::translate(glm::mat4(1.0f), this->position);
}

void Cube::update(double delta) {

}

void Cube::render() {
    vao->bind();
    // Draw primitives, number of indices, datatype of indices, index of indices
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void Cube::destroy() {
    vao->destroy();
    vbo->destroy();
    ebo->destroy();
}