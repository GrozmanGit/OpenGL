#include"VAO.h"

// constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// links VBO to the VAO using a specific layout
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint components, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, components, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// binds VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// unbinds VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// deletes VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
