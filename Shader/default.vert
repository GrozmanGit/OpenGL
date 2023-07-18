#version 330 core

// positions / coordinates
layout (location = 0) in vec3 aPos;
// colors
layout (location = 1) in vec3 aColor;


// outputs the color for the fragment shader
out vec3 color;

// controls the scale of the vertices
uniform float scale;


void main()
{
	// outputs the positions/coordinates of all vertices
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	
	// assigns the colors from the vertex data to "color"
	color = aColor;
}
