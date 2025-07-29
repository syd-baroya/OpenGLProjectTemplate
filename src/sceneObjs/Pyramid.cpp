#include "Pyramid.h"

Pyramid::Pyramid() {

    this->rotation = 0.0f;

    mesh = new Mesh(vertices, indices, std::vector<Texture>());
}

Pyramid::Pyramid(std::vector<Texture> textures) {

    this->rotation = 0.0f;

    mesh = new Mesh(vertices, indices, textures);
}

glm::mat4 Pyramid::getModelMatrix() {
    return glm::translate(glm::mat4(1.0f), this->position) * glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Pyramid::update(double delta) {
    this->rotation += delta*10.0;
}

void Pyramid::render(ShaderProgram& shader) {
    mesh->render(shader);
}

void Pyramid::destroy() {
    mesh->destroy();
}