#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
private:

public:
	
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// binds texture
	void Bind();
	// unbinds texture
	void Unbind();
	// deletes texture
	void Delete();
};

#endif
