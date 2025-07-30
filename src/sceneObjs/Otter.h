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

    void destroy();

private:
    Model* model;
};

#endif