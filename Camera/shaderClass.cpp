#include "shaderClass.h"

// reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}
// constructor that build the shader program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// convert shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// create vertex shader object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// attach vertex shader source to vertex shader object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// compile the vertex shader into machine code
	glCompileShader(vertexShader);
	// error check vertexShader
	compileErrors(vertexShader, "VERTEX");

	// create fragment shader object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// attach fragment shader source to fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// compile vertex shader into machine code
	glCompileShader(fragmentShader);
	// error check fragmentShader
	compileErrors(fragmentShader, "FRAGMENT");

	// create shader program object and get its reference
	ID = glCreateProgram();
	// attach the vertex and fragment shaders to the shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// link shaders together into the shader Program
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");
	// once linked, delete ueless shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

// activates shader program
void Shader::Activate()
{
	glUseProgram(ID);
}

// deletes shader program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			printf("SHADER_COMPILATION_ERROR for: %s\n", type);
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			printf("SHADER_LINKING_ERROR for: %s\n", type);
		}
	}
}
