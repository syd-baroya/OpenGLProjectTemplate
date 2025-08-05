#ifndef PYRAMID_H
#define PYRAMID_H

#include "SceneObject.h"
#include <GLFW/glfw3.h>
#include "Mesh.h"

class Pyramid : public SceneObject {

public:
    Pyramid();
    Pyramid(std::vector<std::shared_ptr<Texture>>& textures);

    void update(double delta);

    void render(ShaderProgram& shader);

private:
    std::unique_ptr<Mesh> mesh;
    // Vertices coordinates
    std::vector<Vertex> vertices =
    { //     COORDINATES     /        COLORS          /   NORMALS    /        TexCoord       //
        //bottom side
        Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 5.0f)},
        Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(5.0f, 5.0f)},
        Vertex{glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(5.0f, 0.0f)},
        
        //left side
        Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec2(5.0f, 0.0f)},
        Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(0.92f, 0.86f, 0.76f), glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec2(2.5f, 5.0f)},
        
        //non-facing side
        Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec2(5.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(0.92f, 0.86f, 0.76f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec2(2.5f, 5.0f)},
        
        //right side
        Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3( 0.83f, 0.70f, 0.44f), glm::vec3(0.8f, 0.5f,  0.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3( 0.83f, 0.70f, 0.44f), glm::vec3(0.8f, 0.5f,  0.0f), glm::vec2(5.0f, 0.0f)},
        Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(0.92f, 0.86f, 0.76f), glm::vec3(0.8f, 0.5f,  0.0f), glm::vec2(2.5f, 5.0f)},
        
        //facing side
        Vertex{glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3( 0.83f, 0.70f, 0.44f), glm::vec3(0.0f, 0.5f,  0.8f), glm::vec2(5.0f, 0.0f)},
        Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3( 0.83f, 0.70f, 0.44f), glm::vec3(0.0f, 0.5f,  0.8f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(0.92f, 0.86f, 0.76f), glm::vec3(0.0f, 0.5f,  0.8f), glm::vec2(2.5f, 5.0f)},
    };


    // Indices for vertices order
    std::vector<GLuint> indices =
    {
        0, 1, 2, // Bottom side
        0, 2, 3, // Bottom side
        4, 6, 5, // Left side
        7, 9, 8, // Non-facing side
        10, 12, 11, // Right side
        13, 15, 14 // Facing side
    };
};

#endif