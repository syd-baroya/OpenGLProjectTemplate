#include "Application.h"


void Application::initObjects() {
    square = new Square();
}
void Application::update() {

}
void Application::render() {
    square->render();
}

void Application::destroy() {
    square->destroy();
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // used keys: escape z
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (key == GLFW_KEY_Z && action == GLFW_RELEASE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
}

void Application::scrollCallback(GLFWwindow* window, double deltaX, double deltaY)
{

}

void Application::mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    double posX, posY;

    if (action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &posX, &posY);
    }
}

void Application::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
}

void Application::resizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
