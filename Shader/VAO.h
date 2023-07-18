#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	// ID reference for the vertex array object
	GLuint ID;
	// constructor that generates a VAO ID
	VAO();

	// links a VBO to the VAO using a specific layout
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint components, GLenum type, GLsizeiptr stride, void* offset);
	// binds VAO
	void Bind();
	// unbinds VAO
	void Unbind();
	// deletes VAO
	void Delete();
};
#endif
