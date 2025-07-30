#include "Cube.h"

Cube::Cube() : SceneObject() {
    mesh = new Mesh(vertices, indices, std::vector<Texture>());
}

glm::mat4 Cube::getModelMatrix() {
    return glm::translate(glm::mat4(1.0f), this->position);
}

void Cube::update(double delta) {

}

void Cube::render(ShaderProgram& shader) {
    mesh->render(shader);
}

void Cube::destroy() {
    mesh->destroy();
}