#include "Cube.h"

Cube::Cube() : SceneObject() {
    mesh = std::make_unique<Mesh>(vertices, indices, std::vector<Texture>());
}

void Cube::update(double delta) {

}

void Cube::render(ShaderProgram& shader) {
    mesh->render(shader);
}