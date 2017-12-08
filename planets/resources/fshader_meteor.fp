#version 330 core
# define GRID 256
# define AMPLITUDE_MULT 0.5
# define FREQUENCY_MULT 2.0
# define AMPLITUDE 1.0
# define FREQUENCY 1.0
# define NUM_LAYERS 5

out vec4 FragColor;

// in vec2 TexCoords;
in vec3 VerCoords;

uniform vec3 planetCol;
uniform int p[GRID];
uniform float r[GRID];

float noise(float in_x)
{
	float x = in_x - int(in_x);

	int floor_x = int((x * 0.5f + 0.5f) * GRID);

	float dist_x = (x * 0.5f + 0.5f) * GRID - floor_x;

	int rx0 = int(mod(floor_x, GRID));
	int rx1 = int(mod(rx0 + 1, GRID));

	float c000 = r[p[rx0]];
	float c100 = r[p[rx1]];

	float sx = smoothstep(0.0f, 1.0f, dist_x);

	return mix(c000, c100, sx);
}

void main()
{
	gl_FragColor = vec4(planetCol, 1.0f); 
}

