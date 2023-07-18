#version 330 core

// outputs colors in RGBA
out vec4 FragColor;

// inputs the color from the vertex shader
in vec3 color;


void main()
{
	FragColor = vec4(color, 1.0f);
}
