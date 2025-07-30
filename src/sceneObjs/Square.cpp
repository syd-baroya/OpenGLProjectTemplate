#include "Square.h"

Square::Square() : SceneObject() {
    mesh = new Mesh(vertices, indices, std::vector<Texture>());
}

Square::Square(std::vector<Texture> textures) {
    mesh = new Mesh(vertices, indices, textures);
}

void Square::update(double delta) {

}

void Square::render(ShaderProgram& shader) {
    mesh->render(shader);
}

void Square::destroy() {
    mesh->destroy();
}