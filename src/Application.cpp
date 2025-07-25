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
    this->camera = new Camera(glm::vec3(0.0f, 1.5f, 3.0f), glm::vec3(0.0f, -0.5f, -1.f), glm::vec3(0.0f, 1.0f, 0.0f), width, height, PERSPECTIVE);

    this->width = width;
    this->height = height;

    initTextures();
    initShaders();
    initObjects();
}

void Application::initTextures() {
    this->woodTexture = new Texture((texturesDir + "woodContainer.jpg").c_str(), "diffuse", 0);
    this->happyFaceTexture = new Texture((texturesDir + "awesomeface.png").c_str(), "diffuse", 1);
}

void Application::initShaders() {
    //this->defaultShader = new ShaderProgram(this->shadersDir + "default.vert", this->shadersDir + "default.frag");
    this->defaultShader = new ShaderProgram(this->shadersDir + "phong.vert", this->shadersDir + "phong.frag");

    this->lightShader = new ShaderProgram(this->shadersDir + "light.vert", this->shadersDir + "light.frag");

    this->lightShader->bind();
    this->lightShader->setVec4("lightColor", this->lightColor);
    this->lightShader->unbind();

    this->defaultShader->bind();
    this->defaultShader->setInt("tex0", this->woodTexture->unit);
    this->defaultShader->setInt("tex1", this->happyFaceTexture->unit);
    this->defaultShader->setVec4("lightColor", this->lightColor);
    this->defaultShader->setVec3("lightPos", this->lightPos);
    this->defaultShader->unbind();

}

void Application::initObjects() {
    this->square = new Square();
    this->pyramid = new Pyramid();
    this->lightCube = new Cube();

    this->lightCube->setPosition(this->lightPos);
    this->pyramid->setPosition(glm::vec3(0, 0, 0));
}

void Application::update() {
    this->time->update();

    double delta = this->time->getDelta();
    this->square->update(delta);
    this->pyramid->update(delta);
}

void Application::render() {
    this->defaultShader->bind();

     this->woodTexture->bind();
     this->happyFaceTexture->bind();

    const glm::mat4 projMat = this->camera->getProjectionMatrix();
    const glm::mat4 viewMat = this->camera->getViewMatrix();
    glm::mat4 modelMat;

    this->defaultShader->setMat4("view", viewMat);
    this->defaultShader->setMat4("proj", projMat);
    this->defaultShader->setVec3("camPos", this->camera->getPosition());

    modelMat = this->square->getModelMatrix();
    this->defaultShader->setMat4("model", modelMat);
    this->square->render();

    modelMat = this->pyramid->getModelMatrix();
    this->defaultShader->setMat4("model", modelMat);
    this->pyramid->render();

    this->woodTexture->unbind();
    this->happyFaceTexture->unbind();

    this->defaultShader->unbind();

    this->lightShader->bind();

    this->lightShader->setMat4("view", viewMat);
    this->lightShader->setMat4("proj", projMat);

    modelMat = this->lightCube->getModelMatrix();
    this->lightShader->setMat4("model", modelMat);
    this->lightCube->render();

    this->lightShader->unbind();
}

void Application::destroy() {
    this->square->destroy();
    this->pyramid->destroy();
    this->woodTexture->destroy();
    this->happyFaceTexture->destroy();
    this->defaultShader->destroy();
    this->lightShader->destroy();
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

    if (key == GLFW_KEY_W && (action == GLFW_PRESS || this->holdingDownKey)) {
        this->camera->processMovement(FORWARD, this->time->getDelta());
        this->holdingDownKey = true;
    }
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || this->holdingDownKey)) {
        this->camera->processMovement(BACKWARD, this->time->getDelta());
        this->holdingDownKey = true;
    }
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || this->holdingDownKey)) {
        this->camera->processMovement(LEFT, this->time->getDelta());
        this->holdingDownKey = true;
    }
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || this->holdingDownKey)) {
        this->camera->processMovement(RIGHT, this->time->getDelta());
        this->holdingDownKey = true;
    }
    if (key == GLFW_KEY_E && (action == GLFW_PRESS || this->holdingDownKey)) {
        this->camera->processMovement(UP, this->time->getDelta());
        this->holdingDownKey = true;
    }
    if (key == GLFW_KEY_C && (action == GLFW_PRESS || this->holdingDownKey)) {
        this->camera->processMovement(DOWN, this->time->getDelta());
        this->holdingDownKey = true;
    }
    if (action == GLFW_RELEASE) {
        this->holdingDownKey = false;
    }
}

void Application::scrollCallback(GLFWwindow* window, double deltaX, double deltaY)
{
    this->camera->processZoom(deltaY);
}

void Application::mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        // Hides mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // Prevents camera from jumping on the first click
        if (this->mouseClicked)
        {
            glfwSetCursorPos(window, (this->width / 2.f), (this->height / 2.f));
            this->mouseClicked = false;
        }

    } else if (action == GLFW_RELEASE)
    {
        this->mouseClicked = true;
        // Unhides cursor since camera is not looking around anymore
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

}

void Application::cursorPosCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (!this->mouseClicked)
    {
        this->camera->processLook(xposIn, yposIn, this->time->getDelta());
        glfwSetCursorPos(window, (this->width / 2.f), (this->height / 2.f));
    }
}

void Application::resizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
