#include "Otter.h"

Otter::Otter(const char* path = "") : SceneObject() {
    model = new Model(path);
}

glm::mat4 Otter::getModelMatrix() {
    return  glm::translate(glm::mat4(1.0f), this->position) * glm::scale(glm::mat4(1.0f), this->scale);
}

void Otter::update(double delta) {

}

void Otter::render(ShaderProgram& shader) {
    model->render(shader);
}

void Otter::destroy() {
    model->destroy();
}