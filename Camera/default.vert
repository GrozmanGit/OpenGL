#version 330 core

// positions / coordinates
layout (location = 0) in vec3 aPos;
// colors
layout (location = 1) in vec3 aColor;
// texture
layout (location = 2) in vec2 aTex;

// outputs the color for fragment shader
out vec3 color;
// outputs the texture for fragment shader
out vec2 texCoord; 

// imports camera matrix from main function
uniform mat4 camMatrix;


void main()
{
	// outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(aPos, 1.0);
	
	// assigns the colors from the vertex data to "color"
	color = aColor;

	// assigns texture coordinate from vertex data to "texCoord"
	texCoord = aTex;
}
