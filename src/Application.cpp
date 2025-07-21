#include "Application.h"


Time::Time() {
    this->currTime = glfwGetTime();
    this->prevTime = this->currTime;
    this->deltaTime = 0.0;
}

void Time::update() {
    // Simple timer
    this->currTime = glfwGetTime();
    this->deltaTime = this->currTime - this->prevTime;
    if (this->deltaTime >= 1 / 60)
    {
        this->prevTime = this->currTime;
    }
}

double Time::getDelta() {
    return this->deltaTime;
}

void Application::init(unsigned int width, unsigned int height) {
    this->time = new Time();
    this->camera = new Camera(width, height, PERSPECTIVE);
    this->width = width;
    this->height = height;

    initShaders();
    initTextures();
    initObjects();
}

void Application::initTextures() {
    this->woodTexture = new Texture((texturesDir + "woodContainer.jpg").c_str(), "diffuse", 0);
    this->happyFaceTexture = new Texture((texturesDir + "awesomeface.png").c_str(), "diffuse", 1);

    this->woodTexture->assign(pyramidShader, "tex0");
    this->happyFaceTexture->assign(pyramidShader, "tex1");
}

void Application::initShaders() {
    this->pyramidShader = new ShaderProgram(shadersDir + "default.vert", shadersDir + "default.frag");
}

void Application::initObjects() {
    this->square = new Square();
    this->pyramid = new Pyramid();
}
void Application::update() {
    this->time->update();

    double delta = this->time->getDelta();
    this->square->update(delta);
    this->pyramid->update(delta);
}

void Application::render() {
    this->pyramidShader->bind();

    this->woodTexture->bind();
    this->happyFaceTexture->bind();

    const glm::mat4 projMat = this->camera->getProjectionMatrix();
    const glm::mat4 viewMat = this->camera->getViewMatrix();
    glm::mat4 modelMat;

    this->pyramidShader->setMat4("view", viewMat);
    this->pyramidShader->setMat4("proj", projMat);

    modelMat = this->square->getModelMatrix();
    this->pyramidShader->setMat4("model", modelMat);
    this->square->render();

    modelMat = this->pyramid->getModelMatrix();
    this->pyramidShader->setMat4("model", modelMat);
    this->pyramid->render();

    this->woodTexture->unbind();
    this->happyFaceTexture->unbind();

    this->pyramidShader->unbind();
}

void Application::destroy() {
    this->square->destroy();
    this->pyramid->destroy();
    this->woodTexture->destroy();
    this->happyFaceTexture->destroy();
    this->pyramidShader->destroy();
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // used keys: escape z
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        this->camera->processMovement(FORWARD, this->time->getDelta());
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        this->camera->processMovement(BACKWARD, this->time->getDelta());
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        this->camera->processMovement(LEFT, this->time->getDelta());
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        this->camera->processMovement(RIGHT, this->time->getDelta());
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        this->camera->processMovement(UP, this->time->getDelta());
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        this->camera->processMovement(DOWN, this->time->getDelta());
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        this->camera->processLook(LOOK_UP, this->time->getDelta());
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        this->camera->processLook(LOOK_DOWN, this->time->getDelta());
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        this->camera->processLook(LOOK_LEFT, this->time->getDelta());
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        this->camera->processLook(LOOK_RIGHT, this->time->getDelta());
    }

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
    this->camera->processZoom(deltaY);
}

void Application::mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    double posX, posY;

    if (action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &posX, &posY);
    }
}

void Application::cursorPosCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (this->firstMouse)
    {
        this->lastX = width / 2.0f;
        this->lastY = height / 2.0f;
        this->firstMouse = false;
    }

    float xoffset = xpos - this->lastX;
    float yoffset = this->lastY - ypos; // reversed since y-coordinates go from bottom to top

    this->lastX = xpos;
    this->lastY = ypos;

    //this->camera->processLook(xoffset, yoffset, this->time->getDelta());
}

void Application::resizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
