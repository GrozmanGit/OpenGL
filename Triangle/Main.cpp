#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// vertex Shader source code
const char* vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// fragment Shader source code
const char* fragmentShaderSource = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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

    GLfloat verticies[] =
    {
        // Left Corner
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        // Right Corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        // Top Corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
    };
    
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
    // create vertex shader object and get refernece
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // attach vertex shader source to vertex shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // compile vertex shader into machine code
    glCompileShader(vertexShader);

    // create fragment shader object and get refernce
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // attach fragmnet shader source to fragmnet shader object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // compile fragmnet shader into machine code
    glCompileShader(fragmentShader);

    // create shader program object and get refernece
    GLuint shaderProgram = glCreateProgram();

    // attach vertex and fragment shader to shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // link shaders together in shader program
    glLinkProgram(shaderProgram);

    // once linked, delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // create reference containers for VAO and VBO
    GLuint VAO, VBO;

    // generate VAO and VBO with 1 refernce
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // make VAO current by binding 
    glBindVertexArray(VAO);
    // bind VBO, specifying its a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // GL_STREAM --> verticies will be modified once after used few times
    // GL_STATIC --> verticies will be modified once and used many times
    // GL_DYNAMIC --> verticies will be modified multiple times and used many times
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
    // VAO positon, 3 verticies, float vertex value, int vertex value, data between each vertex, pointer to verticies
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // VAO position
    glEnableVertexAttribArray(0);
    // if VBO/VAO accidently changed, unbind to 0
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // specify background color
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // clear back buffer, assign new color
    glClear(GL_COLOR_BUFFER_BIT);
    // swap buffers to view background
    glfwSwapBuffers(window);

    // main window runner
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        // process GLFW events
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Destroy window before temrination 
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
