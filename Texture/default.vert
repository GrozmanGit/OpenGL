#version 330 core

// positions / coordinates
layout (location = 0) in vec3 aPos;
// colors
layout (location = 1) in vec3 aColor;
// texture coordinates
layout (location = 2) in vec2 aTex;

// outputs the color for the fragment shader
out vec3 color;

// outputs texture coordinates to fragment shader
out vec2 texCoord;

// controls scale of vertices
uniform float scale;

void main()
{
	// outputs the positions / coordinates of all vertices
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	
	// assigns the colors from the vertex data to "color"
	color = aColor;

	// assigns texture coordinates to "texCoord"
	texCoord = aTex;
}
