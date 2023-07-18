#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	// ID reference of element[s] buffer object
	GLuint ID;
	// constructor that generates a EBO and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);

	// binds EBO
	void Bind();
	// unbinds EBO
	void Unbind();
	// deletes EBO
	void Delete();
};

#endif
