#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include "WindowManager.h"
#include "Application.h"

const unsigned int width = 800;
const unsigned int height = 800;

int main(void)
{
  
    Application* application = new Application(width, height);
    WindowManager* windowManager = new WindowManager();

    windowManager->init(width, height);
    windowManager->setEventCallbacks(application);

    application->init();

    glEnable(GL_DEPTH_TEST);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(windowManager->getHandle()))
    {
        /* Render here */
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        application->update();
        application->render();

        /* Swap front and back buffers */
        glfwSwapBuffers(windowManager->getHandle());

        /* Poll for and process events */
        glfwPollEvents();
    }

    // Delete all the objects we've created
    application->destroy();

    // Delete window before ending the program
    glfwDestroyWindow(windowManager->getHandle());

    glfwTerminate();
    return 0;
}