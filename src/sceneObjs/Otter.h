#ifndef OTTER_H
#define OTTER_H

#include "SceneObject.h"
#include <GLFW/glfw3.h>
#include "Model.h"

class Otter : public SceneObject {
public:
    Otter(const char* path);
    void update(double delta);

    void render(ShaderProgram& shader);

private:
    std::unique_ptr<Model> model;
};

#endif