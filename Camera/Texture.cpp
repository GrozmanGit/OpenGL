#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	// assigns texture type of texture to texture object
	type = texType;
	// stores width, height, texture color channels
	int widthImg, heightImg, colCh;
	// flips image to appear right-side up
	stbi_set_flip_vertically_on_load(true);
	// reads image from file and stores in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &colCh, 0);

	// generates OpenGL texture object
	glGenTextures(1, &ID);
	// assigns the texture to a texture unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// configures algorithm used to minimize or magnify texture
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// configures way texture repeats
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// assigns image to OpenGL texture object
	glTexImage2D(texType, 0, GL_RGB, widthImg, heightImg, 0, format, pixelType, bytes);
	// generates mipmap
	glGenerateMipmap(texType);
	// deletes image data after being loaded in OpenGL object
	stbi_image_free(bytes);
	// unbinds texture object to not be accidently modified
	glBindTexture(texType, 0);
}

// assigns a texture unit to a texture
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// gets location of uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// shader needs to be activated before changing value of uniform
	shader.Activate();
	// sets value of uniform
	glUniform1i(texUni, unit);
}

// binds texture
void Texture::Bind()
{
	glBindTexture(type, ID);
}

// unbinds texture
void Texture::Unbind()
{
	glBindTexture(type, 0);
}

// deletes texture
void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
