#include "Application.h"


void Application::init(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
    // Variables that help the rotation of the pyramid
    this->rotation = 0.0f;
    this->prevTime = glfwGetTime();
    initShaders();
    initTextures();
    initObjects();
}

void Application::initTextures() {
    this->woodTexture = new Texture((texturesDir + "woodContainer.jpg").c_str(), "diffuse", 0);
    this->happyFaceTexture = new Texture((texturesDir + "awesomeface.png").c_str(), "diffuse", 1);

    this->woodTexture->assign(pyramidShader, "tex0");
    this->happyFaceTexture->assign(pyramidShader, "tex1");

    this->woodTexture->assign(squareShader, "tex0");
    this->happyFaceTexture->assign(squareShader, "tex1");

}

void Application::initShaders() {
    this->pyramidShader = new ShaderProgram(shadersDir + "default.vert", shadersDir + "default.frag");
    this->squareShader = new ShaderProgram(shadersDir + "default.vert", shadersDir + "default.frag");

    // Gets ID of uniform called "scale"
    this->uniID = glGetUniformLocation(pyramidShader->ID, "scale");
}

void Application::initObjects() {
    this->square = new Square();
    this->pyramid = new Pyramid();
}
void Application::update() {
    // Simple timer
    double crntTime = glfwGetTime();
    if (crntTime - this->prevTime >= 1 / 60)
    {
        this->rotation += 0.5f;
        this->prevTime = crntTime;
    }
    this->squareShader->bind();
    this->square->update(this->rotation, (float)this->width / this->height, this->squareShader->ID);
    this->squareShader->unbind();

    this->pyramidShader->bind();
    this->pyramid->update(this->rotation, (float)this->width / this->height, this->pyramidShader->ID);
    this->pyramidShader->unbind();
}
void Application::render() {
    this->pyramidShader->bind();
    // Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
    glUniform1f(uniID, 0.5f);
    this->woodTexture->bind();
    this->happyFaceTexture->bind();
    this->pyramid->render();
    this->woodTexture->unbind();
    this->happyFaceTexture->unbind();
    this->pyramidShader->unbind();

    this->squareShader->bind();
    this->woodTexture->bind();
    this->happyFaceTexture->bind();
    this->square->render();
    this->woodTexture->unbind();
    this->happyFaceTexture->unbind();
    this->squareShader->unbind();
}

void Application::destroy() {
    this->square->destroy();
    this->pyramid->destroy();
    this->woodTexture->destroy();
    this->happyFaceTexture->destroy();
    this->pyramidShader->destroy();
    this->squareShader->destroy();
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
