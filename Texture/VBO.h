#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	// reference ID of the vertex buffer object
	GLuint ID;
	// constructor that generates a VBO and links it to vertices
	VBO(GLfloat* vertices, GLsizeiptr size);

	// binds VBO
	void Bind();
	// inbinds VBO
	void Unbind();
	// deletes VBO
	void Delete();
};

#endif
