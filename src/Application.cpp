#include "Application.h"


void Application::init() {
    initShaders();
    initTextures();
    initObjects();
}

void Application::initTextures() {
    woodTexture = new Texture((texturesDir + "woodContainer.jpg").c_str(), "diffuse", 0);
    happyFaceTexture = new Texture((texturesDir + "awesomeface.png").c_str(), "diffuse", 1);
    woodTexture->assign(defaultShader, "tex0");
    happyFaceTexture->assign(defaultShader, "tex1");

}

void Application::initShaders() {
    defaultShader = new ShaderProgram(shadersDir + "default.vert", shadersDir + "default.frag");

    // Gets ID of uniform called "scale"
    uniID = glGetUniformLocation(defaultShader->ID, "scale");
}

void Application::initObjects() {
    square = new Square();
}
void Application::update() {

}
void Application::render() {
    defaultShader->bind();
    // Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
    glUniform1f(uniID, 0.5f);
    woodTexture->bind();
    happyFaceTexture->bind();
    square->render();
    woodTexture->unbind();
    happyFaceTexture->unbind();
    defaultShader->unbind();
}

void Application::destroy() {
    square->destroy();
    woodTexture->destroy();
    happyFaceTexture->destroy();
    defaultShader->destroy();
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
