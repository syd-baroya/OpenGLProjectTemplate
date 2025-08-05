#include "Pyramid.h"
#include <memory>

Pyramid::Pyramid() : SceneObject() {
    mesh = std::make_unique<Mesh>(vertices, indices, std::vector<std::shared_ptr<Texture>>());
}

Pyramid::Pyramid(std::vector<std::shared_ptr<Texture>>& textures) {
    mesh = std::make_unique<Mesh>(vertices, indices, textures);
}

void Pyramid::update(double delta) {
    this->orientation.y += delta*10.0;
}

void Pyramid::render(ShaderProgram& shader) {
    mesh->render(shader);
}