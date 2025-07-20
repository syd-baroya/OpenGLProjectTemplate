#include <iostream>

#include "WindowManager.h"
#include "Application.h"


int main(void)
{
  
    Application* application = new Application();
    WindowManager* windowManager = new WindowManager();

    windowManager->init(800, 800);
    windowManager->setEventCallbacks(application);

    application->init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(windowManager->getHandle()))
    {
        /* Render here */
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind the VAO so OpenGL knows to use it
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