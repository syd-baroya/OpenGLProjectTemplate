#include "Pyramid.h"

Pyramid::Pyramid() {
    // Generates Vertex Array Object and binds it
    vao = new VAO();
    vao->bind();

    // Generates Vertex Buffer Object and links it to vertices
    vbo = new VBO(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    ebo = new EBO(indices, sizeof(indices));

    // Links VBO attributes such as coordinates and colors to VAO
    vao->linkAttrib(*vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao->linkAttrib(*vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao->linkAttrib(*vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    vao->unbind();
    vbo->unbind();
    ebo->unbind();
}

void Pyramid::update(float rotation, float aspect, GLuint shaderID) {

    // Initializes matrices so they are not the null matrix
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    // Assigns different transformations to each matrix
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
    proj = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

    // Outputs the matrices into the Vertex Shader
    int modelLoc = glGetUniformLocation(shaderID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shaderID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projLoc = glGetUniformLocation(shaderID, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
}

void Pyramid::render() {
    vao->bind();
    // Draw primitives, number of indices, datatype of indices, index of indices
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void Pyramid::destroy() {
    vao->destroy();
    vbo->destroy();
    ebo->destroy();
}