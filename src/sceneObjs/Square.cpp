#include "Square.h"

Square::Square() : SceneObject() {
    mesh = std::make_unique<Mesh>(vertices, indices, std::vector<Texture>());
}

Square::Square(std::vector<Texture> textures) {
    mesh = std::make_unique<Mesh>(vertices, indices, textures);
}

void Square::update(double delta) {

}

void Square::render(ShaderProgram& shader) {
    mesh->render(shader);
}