#version 330 core
# define SIZE 768
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
uniform float time;
uniform int p[SIZE];
uniform vec3 g[GRID];

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
	float inv_dist_x = -1.0f + dist_x;
	float inv_dist_y = -1.0f + dist_y;
	float inv_dist_z = -1.0f + dist_z;

	int x0 = int(mod(floor_x, GRID));
	int x1 = int(mod(x0 + 1.0f, GRID));
	int y0 = int(mod(floor_y, GRID));
	int y1 = int(mod(y0 + 1.0f, GRID));
	int z0 = int(mod(floor_z, GRID));
	int z1 = int(mod(z0 + 1.0f, GRID));

	float sx = smoothstep(0.0f, 1.0f, dist_x);
	float sy = smoothstep(0.0f, 1.0f, dist_y);
	float sz = smoothstep(0.0f, 1.0f, dist_z);

	vec3 g000 = g[p[p[p[x0] + y0] + z0]];
	vec3 g100 = g[p[p[p[x1] + y0] + z0]];
	vec3 g010 = g[p[p[p[x0] + y1] + z0]];
	vec3 g110 = g[p[p[p[x1] + y1] + z0]];
	vec3 g001 = g[p[p[p[x0] + y0] + z1]];
	vec3 g101 = g[p[p[p[x1] + y0] + z1]];
	vec3 g011 = g[p[p[p[x0] + y1] + z1]];
	vec3 g111 = g[p[p[p[x1] + y1] + z1]];

	float c000 = dot(g000, normalize(vec3(dist_x, dist_y, dist_z)));
	float c100 = dot(g100, normalize(vec3(inv_dist_x, dist_y, dist_z)));
	float c010 = dot(g010, normalize(vec3(dist_x, inv_dist_y, dist_z)));
	float c110 = dot(g110, normalize(vec3(inv_dist_x, inv_dist_y, dist_z)));
	float c001 = dot(g001, normalize(vec3(dist_x, dist_y, inv_dist_z)));
	float c101 = dot(g101, normalize(vec3(inv_dist_x, dist_y, inv_dist_z)));
	float c011 = dot(g011, normalize(vec3(dist_x, inv_dist_y, inv_dist_z)));
	float c111 = dot(g111, normalize(vec3(inv_dist_x, inv_dist_y, inv_dist_z)));
	
	float nx00 = mix(c000, c100, sx);
	float nx10 = mix(c010, c110, sx);
	float nx01 = mix(c001, c101, sx);
	float nx11 = mix(c011, c111, sx);
	float ny0 = mix(nx00, nx10, sy);
	float ny1 = mix(nx01, nx11, sy);

	return 0.5f + 0.5f * mix(ny0, ny1, sz);
}

void main()
{
	float frac_noise = 0.0f;
	float ampl = AMPLITUDE;
	float freq = FREQUENCY;
	float ampl_mult = AMPLITUDE_MULT;
	float freq_mult = FREQUENCY_MULT;
	vec3 frac_vec = VerCoords * freq;
	for(int i = 0; i != 5; ++i)
	{
		frac_noise += noise(frac_vec.x, frac_vec.y, frac_vec.z) * ampl;
		ampl *= ampl_mult;
		freq *= freq_mult;
		frac_vec *= freq;
	}
	gl_FragColor =  frac_noise * vec4(planetCol, 1.0);
}

