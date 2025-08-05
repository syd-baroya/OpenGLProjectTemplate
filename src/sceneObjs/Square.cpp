#include "Square.h"
#include <memory>

Square::Square() : SceneObject() {
    mesh = std::make_unique<Mesh>(vertices, indices, std::vector<std::shared_ptr<Texture>>());
}

Square::Square(std::vector<std::shared_ptr<Texture>>& textures) {
    mesh = std::make_unique<Mesh>(vertices, indices, textures);
}

void Square::update(double delta) {

}

void Square::render(ShaderProgram& shader) {
    mesh->render(shader);
}