#pragma once

#ifndef SQUARE_H
#define SQUARE_H

#include "SceneObject.h"
#include <GLFW/glfw3.h>
#include "Mesh.h"

class Square : public SceneObject {

public:
    Square();
    Square::Square(std::vector<std::shared_ptr<Texture>>& textures);

    void update(double delta);

    void render(ShaderProgram& shader);

private:
    std::unique_ptr<Mesh> mesh;
    // Vertices coordinates
    std::vector<Vertex>  vertices =
    {   //     COORDINATES     /                  COLORS                  /           NORMALS         /    TexCoord     //
        Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)}
    };

    // Indices for vertices order
    std::vector<GLuint> indices =
    {
        0, 1, 2,
        0, 2, 3
    };
};

#endif