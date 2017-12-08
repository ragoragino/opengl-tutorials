#version 330 core
# define SIZE 512
# define GRID 256

out vec4 FragColor;

// in vec2 TexCoords;

uniform vec3 planetCol;

void main()
{   
	gl_FragColor = vec4(planetCol, 1.0);
}

