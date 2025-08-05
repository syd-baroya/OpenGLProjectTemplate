#include "Otter.h"

Otter::Otter(const char* path = "") : SceneObject() {
    model = std::make_unique<Model>(path);
}

void Otter::update(double delta) {

}

void Otter::render(ShaderProgram& shader) {
    model->render(shader);
}