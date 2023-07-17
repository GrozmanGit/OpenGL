#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(void)
{
    if (!glfwInit())
    {
        fputs("GLFW initialization failed.", stdout);
        return -1;
    }

    // tell OpenGL version specificiation (v-3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // core profile - modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window object - width, height, title
    GLFWwindow* window = glfwCreateWindow(800, 800, "glproc", NULL, NULL);

    // check if null, send debug msg, terminate
    if (window == nullptr)
    {
        fputs("Failed to create GLFW window.", stdout);
        glfwTerminate();
        return -1;
    }

    // set window to current context
    glfwMakeContextCurrent(window);

    // check if glad lib load
    if (!gladLoadGL())
    {
        fputs("glad initialization failed.", stdout);
        return -1;
    }

    // specify viewport window - x, y, width, height
    glViewport(0, 0, 800, 800);
    
    // specify background color
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // clear back buffer, assign new color
    glClear(GL_COLOR_BUFFER_BIT);
    // swap buffers to view background
    glfwSwapBuffers(window);

    // main window runner
    while (!glfwWindowShouldClose(window))
    {
        // process GLFW events
        glfwPollEvents();
    }

    // Destroy window before temrination
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
