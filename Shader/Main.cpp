#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../shaderClass.h"
#include "../EBO.h"
#include "../VAO.h"
#include "../VBO.h"

GLfloat vertices[] =
{	/*        coordinates            */									  /*    colors    */
	-0.5f,  -0.5f * float(sqrt(3)) / 3,		0.0f, /*lower left corner*/	  0.8f, 0.3f, 0.02f, 
	 0.5f,  -0.5f * float(sqrt(3)) / 3,		0.0f, /*lower right corner*/  0.8f, 0.3f, 0.02f,
	 0.0f,   0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	 /*top corner*/		  1.0f, 0.6f, 0.32f,

	-0.25f,  0.5f * float(sqrt(3)) / 6,		0.0f,    /*inner left*/       0.9f, 0.45f, 0.17f,
	 0.25f,  0.5f * float(sqrt(3)) / 6,		0.0f,    /*inner right*/      0.9f, 0.45f, 0.17f,
	 0.0f,  -0.5f * float(sqrt(3)) / 3,		0.0f,    /*inner bottom*/     0.8f,  0.3f, 0.02f 
};

// indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // lower left triangle
	3, 2, 4, // lower right triangle
	5, 4, 1  // upper triangle
};

int main()
{
	// initialize GLFW
	if (!glfwInit())
	{
		fputs("failed to initialize GLFW", stdout);
		return -1;
	}

	// tell OpenGL version --> (v-3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// specifiy OpenGL to use modern functions (Core Profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "window", NULL, NULL);

	if (window == nullptr)
	{
		fputs("failed to create GLFW window", stdout);
		glfwTerminate();
		return -1;
	}
	// introduce window into the current context
	glfwMakeContextCurrent(window);

	// load GLAD --> configures OpenGL
	if (!gladLoadGL())
	{
		fputs("could not load glad", stdout);
		glfwTerminate();
		return -1;
	}
	// specify viewport of OpenGL in the Window
	// x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// generates shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// generate VAO and bind it
	VAO VAO1;
	VAO1.Bind();

	// generate VBO and link to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// generate EBO and link to indices
	EBO EBO1(indices, sizeof(indices));

	// link VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// unbind all to prevent accidental modification
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// get ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// main loop
	while (!glfwWindowShouldClose(window))
	{
		// specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// clean back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// tell OpenGL which shader program to use
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		// bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// draw primitives, #indices, indices datatype, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// swap back buffer with the front buffer
		glfwSwapBuffers(window);
		// process GLFW events
		glfwPollEvents();
	}

	// delete created objects
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// delete window before ending program
	glfwDestroyWindow(window);
	// terminate GLFW before ending program
	glfwTerminate();
	return 0;
}
