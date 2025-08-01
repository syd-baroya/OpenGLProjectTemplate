#version 410 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;

// Normals (not necessarily normalized)
layout (location = 1) in vec3 aNormal;

// Colors
layout (location = 2) in vec3 aColor;

// Texture Coordinates
layout (location = 3) in vec2 aTex;


// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the current position for the Fragment Shader
out vec3 crntPos;

uniform mat4 view;
uniform mat4 proj;
// Imports the model matrix from the main function
uniform mat4 model;


void main()
{
	// calculates current position
	crntPos = vec3(model * vec4(aPos, 1.0f));
	// Outputs the positions/coordinates of all vertices
	gl_Position = proj * view * vec4(crntPos, 1.0);

	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
	// Assigns the normal from the Vertex Data to "Normal"
	Normal = aNormal;
}