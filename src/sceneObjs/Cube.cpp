#include "Cube.h"

Cube::Cube() : SceneObject() {
    mesh = new Mesh(vertices, indices, std::vector<Texture>());
}

void Cube::update(double delta) {

}

void Cube::render(ShaderProgram& shader) {
    mesh->render(shader);
}

void Cube::destroy() {
    //mesh->destroy();
}