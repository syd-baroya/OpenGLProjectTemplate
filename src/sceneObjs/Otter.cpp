#include "Otter.h"

Otter::Otter(const char* path = "") : SceneObject() {
    model = new Model(path);
}

void Otter::update(double delta) {

}

void Otter::render(ShaderProgram& shader) {
    model->render(shader);
}

void Otter::destroy() {
    model->destroy();
}