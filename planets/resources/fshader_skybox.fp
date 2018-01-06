#version 330 core
# define SIZE 768
# define GRID 256
# define AMPLITUDE_MULT 0.5
# define FREQUENCY_MULT 2.0
# define AMPLITUDE 1.0
# define FREQUENCY 1.0
# define NUM_LAYERS 5

out vec3 FragColor;

in vec3 VerCoords;

uniform int p[SIZE];
uniform float r[GRID];

float noise(float in_x, float in_y, float in_z)
{
	float x = in_x - int(in_x);
	float y = in_y - int(in_y);
	float z = in_z - int(in_z);

	int floor_x = int((x * 0.5f + 0.5f) * GRID);
	int floor_y = int((y * 0.5f + 0.5f) * GRID);
	int floor_z = int((z * 0.5f + 0.5f) * GRID);

	float dist_x = (x * 0.5f + 0.5f) * GRID - floor_x;
	float dist_y = (y * 0.5f + 0.5f) * GRID - floor_y;
	float dist_z = (z * 0.5f + 0.5f) * GRID - floor_z;

	int rx0 = int(mod(floor_x, GRID));
	int rx1 = int(mod(rx0 + 1, GRID));
	int ry0 = int(mod(floor_y, GRID));
	int ry1 = int(mod(ry0 + 1, GRID));
	int rz0 = int(mod(floor_z, GRID));
	int rz1 = int(mod(rz0 + 1, GRID));

	float c000 = r[p[p[p[rx0] + ry0] + rz0]];
	float c100 = r[p[p[p[rx1] + ry0] + rz0]];
	float c010 = r[p[p[p[rx0] + ry1] + rz0]];
	float c110 = r[p[p[p[rx1] + ry1] + rz0]];
	float c001 = r[p[p[p[rx0] + ry0] + rz1]];
	float c101 = r[p[p[p[rx1] + ry0] + rz1]];
	float c011 = r[p[p[p[rx0] + ry1] + rz1]];
	float c111 = r[p[p[p[rx1] + ry1] + rz1]];

	float sx = smoothstep(0.0f, 1.0f, dist_x);
	float sy = smoothstep(0.0f, 1.0f, dist_y);
	float sz = smoothstep(0.0f, 1.0f, dist_z);

	float nx00 = mix(c000, c100, sx);
	float nx10 = mix(c010, c110, sx);
	float nx01 = mix(c001, c101, sx);
	float nx11 = mix(c011, c111, sx);
	float ny0 = mix(nx00, nx10, sy);
	float ny1 = mix(nx01, nx11, sy);

	return mix(ny0, ny1, sz);
}

void main()
{
	float frac_noise = 0.0f;
	float ampl = 8.0f;
	float freq = 4.0f;
	float ampl_mult = 0.1f;
	float freq_mult = 2.5f;
	vec3 frac_vec = VerCoords * freq;
	for(int i = 0; i != 5; ++i)
	{
		frac_noise += noise(frac_vec.x, frac_vec.y, frac_vec.z) * ampl;
		ampl *= ampl_mult;
		freq *= freq_mult;
		frac_vec *= freq;
	}

	gl_FragColor = clamp(1 - frac_noise, 0.0f, 1.0f) * vec4(1.0);
}

