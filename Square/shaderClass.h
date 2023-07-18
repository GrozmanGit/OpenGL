#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
private:
	void compileErrors(unsigned int shader, const char* type);

public:
	// reference ID of the shader program
	GLuint ID;
	// constructor to build the shader program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// activates shader program
	void Activate();
	// deletes shader program
	void Delete();

};

#endif
