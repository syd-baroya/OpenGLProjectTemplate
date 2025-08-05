#include "Application.h"
#include <memory>

Time::Time() {
    this->currTime = glfwGetTime();
    this->prevTime = this->currTime;
    this->deltaTime = 0.0;
}

void Time::update() {
    this->currTime = glfwGetTime();
    this->deltaTime = this->currTime - this->prevTime;
    if (this->deltaTime >= 1.0 / 60.0) {
        this->prevTime = this->currTime;
    }
}

double Time::getDelta() {
    return this->deltaTime;
}

Application::Application(unsigned int width, unsigned int height)
    : camera(glm::vec3(0.0f, 1.5f, 3.0f), glm::vec3(0.0f, -0.5f, -1.f), glm::vec3(0.0f, 1.0f, 0.0f), width, height, PERSPECTIVE),
      width(width), height(height)
{

}

void Application::init() {
    initTextures();
    initShaders();
    initObjects();
}

void Application::initTextures() {
    this->woodTexture = std::make_shared<Texture>((texturesDir + "woodContainer_diffuse.jpg").c_str(), "diffuse", 0);
    this->happyTexture = std::make_shared<Texture>((texturesDir + "awesomeface_diffuse.png").c_str(), "diffuse", 1);
}

void Application::initShaders() {
    this->phongShader = new ShaderProgram(this->shadersDir + "phong.vert", this->shadersDir + "phong.frag");

    this->lightShader = new ShaderProgram(this->shadersDir + "light.vert", this->shadersDir + "light.frag");

    this->defaultShader = new ShaderProgram(this->shadersDir + "default.vert", this->shadersDir + "default.frag");

    this->lightShader->bind();
    this->lightShader->setVec4("lightColor", this->lightColor);
    this->lightShader->unbind();

    this->phongShader->bind();
    this->phongShader->setVec4("lightColor", this->lightColor);
    this->phongShader->setVec3("lightPos", this->lightPos);
    this->phongShader->unbind();
}

void Application::initObjects() {

    this->square = new Square(std::vector<std::shared_ptr<Texture>>{ this->woodTexture });
    this->pyramid = new Pyramid(std::vector<std::shared_ptr<Texture>>{ this->happyTexture });
    this->lightCube = new Cube();

    this->lightCube->setPosition(this->lightPos);

    this->otter = new Otter((this->modelsDir + "otter/otter.dae").c_str());
    this->otter->setPosition(glm::vec3(0.25f, 0.0f, 0.5f));
    std::cout << "finished initializing objects" << std::endl;
}

void Application::update() {
    this->time.update();

    double delta = this->time.getDelta();
    this->square->update(delta);
    this->pyramid->update(delta);
}

void Application::render() {
    const glm::mat4 projMat = this->camera.getProjectionMatrix();
    const glm::mat4 viewMat = this->camera.getViewMatrix();
    glm::mat4 modelMat;

    this->phongShader->bind();

    this->phongShader->setMat4("view", viewMat);
    this->phongShader->setMat4("proj", projMat);
    this->phongShader->setVec3("camPos", this->camera.getPosition());

    modelMat = this->square->getModelMatrix();
    this->phongShader->setMat4("model", modelMat);
    this->square->render(*this->phongShader);

    modelMat = this->pyramid->getModelMatrix();
    this->phongShader->setMat4("model", modelMat);
    this->pyramid->render(*this->phongShader);

    modelMat = this->otter->getModelMatrix();
    this->phongShader->setMat4("model", modelMat);
    this->otter->render(*this->phongShader);

    this->phongShader->unbind();

    this->lightShader->bind();

    this->lightShader->setMat4("view", viewMat);
    this->lightShader->setMat4("proj", projMat);

    modelMat = this->lightCube->getModelMatrix();
    this->lightShader->setMat4("model", modelMat);
    this->lightCube->render(*this->lightShader);

    this->lightShader->unbind();
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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
        this->camera.processMovement(FORWARD, this->time.getDelta());
        this->holdingDownKey = true;
    }
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || this->holdingDownKey)) {
        this->camera.processMovement(BACKWARD, this->time.getDelta());
        this->holdingDownKey = true;
    }
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || this->holdingDownKey)) {
        this->camera.processMovement(LEFT, this->time.getDelta());
        this->holdingDownKey = true;
    }
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || this->holdingDownKey)) {
        this->camera.processMovement(RIGHT, this->time.getDelta());
        this->holdingDownKey = true;
    }
    if (key == GLFW_KEY_E && (action == GLFW_PRESS || this->holdingDownKey)) {
        this->camera.processMovement(UP, this->time.getDelta());
        this->holdingDownKey = true;
    }
    if (key == GLFW_KEY_C && (action == GLFW_PRESS || this->holdingDownKey)) {
        this->camera.processMovement(DOWN, this->time.getDelta());
        this->holdingDownKey = true;
    }
    if (action == GLFW_RELEASE) {
        this->holdingDownKey = false;
    }
}

void Application::scrollCallback(GLFWwindow* window, double deltaX, double deltaY) {
    this->camera.processZoom(deltaY);
}

void Application::mouseCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        if (this->mouseClicked) {
            glfwSetCursorPos(window, (this->width / 2.f), (this->height / 2.f));
            this->mouseClicked = false;
        }
    } else if (action == GLFW_RELEASE) {
        this->mouseClicked = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void Application::cursorPosCallback(GLFWwindow* window, double xposIn, double yposIn) {
    if (!this->mouseClicked) {
        this->camera.processLook(xposIn, yposIn, this->time.getDelta());
        glfwSetCursorPos(window, (this->width / 2.f), (this->height / 2.f));
    }
}

void Application::resizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
    this->camera.resize(width, height);
}

void Application::destroy() {}
