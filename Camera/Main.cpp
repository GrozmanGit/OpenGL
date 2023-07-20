#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "shaderClass.h"
#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

GLfloat vertices[] =
{	/*  coordinates  */		/*    colors    */  /* texcoord */
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main(void)
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

	GLFWwindow* window = glfwCreateWindow(width, height, "window", NULL, NULL);

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
	glViewport(0, 0, width, height);

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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// unbind all to prevent accidental modification
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// texture
	Texture texture("stoneTexture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	texture.texUnit(shaderProgram, "tex0", 0);

	// enables depth buffer
	glEnable(GL_DEPTH_TEST);

	// creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// main loop
	while (!glfwWindowShouldClose(window))
	{
		// specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// clean back buffer and assign depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// tell OpenGL which shader program to use
		shaderProgram.Activate();
		// handles camera events
		camera.Inputs(window);
		// updates & exports camera matrix to vertex shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// binds texture to appear in rendering
		texture.Bind();
		// bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// draw primitives, #indices, indices datatype, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		// swap back buffer with the front buffer
		glfwSwapBuffers(window);
		// process GLFW events
		glfwPollEvents();
	}

	// delete created objects
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	texture.Delete();
	shaderProgram.Delete();
	// delete window before ending program
	glfwDestroyWindow(window);
	// terminate GLFW before ending program
	glfwTerminate();
	return 0;
}
