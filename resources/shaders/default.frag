#version 410 core

// Outputs colors in RGBA
out vec4 glColor;


// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Unit
uniform sampler2D tex0;
uniform sampler2D tex1;

void main()
{
	glColor = vec4(color, 1.0f);
	//glColor = texture(tex0, texCoord);
	//glColor = mix(texture(tex0, texCoord), texture(tex1, texCoord), 0.2);
}