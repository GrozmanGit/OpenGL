#version 330 core

// outputs colors in RGBA
out vec4 FragColor;

// inputs the color from vertex shader
in vec3 color;

// inputs the texture from vertex shader
in vec2 texCoord;

// gets texture unit from main function
uniform sampler2D tex0;

void main()
{
	FragColor = texture(tex0, texCoord);
}
