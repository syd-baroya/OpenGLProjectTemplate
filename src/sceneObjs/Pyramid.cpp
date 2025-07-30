#include "Pyramid.h"

Pyramid::Pyramid() : SceneObject() {
    mesh = new Mesh(vertices, indices, std::vector<Texture>());
}

Pyramid::Pyramid(std::vector<Texture> textures) {
    mesh = new Mesh(vertices, indices, textures);
}

void Pyramid::update(double delta) {
    this->orientation.y += delta*10.0;
}

void Pyramid::render(ShaderProgram& shader) {
    mesh->render(shader);
}

void Pyramid::destroy() {
    mesh->destroy();
}