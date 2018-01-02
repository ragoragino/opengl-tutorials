# pragma once
# include "Header.h"
# define SIZE 768
# define GRID 256

/*
Arrays and initializer for a Perlin noise function.
The implementation is in fragment shader shader_sun.fp.
*/

// Index array

static int p[SIZE] = { 151, 160, 137, 91, 90, 15,
131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};


static glm::vec3 g[GRID]; // Random gradients array: (0.0, 1.0)

void perlin_init_buffers()
{
	for (int i = 0; i != GRID * 2; ++i)
	{
		int index = int(rand() % GRID);
		p[i + GRID] = p[index];
	}

	for (int i = 0; i != GRID; ++i)
	{
		g[i] = glm::normalize(glm::vec3(-1.0f + 2.0f * rand() / (RAND_MAX + 1.0),
			-1.0f + 2.0f * rand() / (RAND_MAX + 1.0), 
			-1.0f + 2.0f * rand() / (RAND_MAX + 1.0)));
	}
}

template<typename T>
T smoothstep(T edge0, T edge1, T x)
{
	T t = (x - edge0) / (edge1 - edge0);
	t > 1.0 ? 1.0 : (t < 0.0 ? 0.0 : t);
	return t * t * (3.0 - 2.0 * t);
}

template<typename T>
T lerp(T a, T b, T t)
{
	return a * (1 - t) + b * t;
}

// 3D Perlin Noise
float perlin_noise(float x, float y, float z)
{
	int floor_x = int((x * 0.5f + 0.5f) * GRID);
	int floor_y = int((y * 0.5f + 0.5f) * GRID);
	int floor_z = int((z * 0.5f + 0.5f) * GRID);

	float dist_x = (x * 0.5f + 0.5f) * GRID - floor_x;
	float dist_y = (y * 0.5f + 0.5f) * GRID - floor_y;
	float dist_z = (z * 0.5f + 0.5f) * GRID - floor_z;
	float inv_dist_x = -1.0 + dist_x;
	float inv_dist_y = -1.0 + dist_y;
	float inv_dist_z = -1.0 + dist_z;

	int x0 = int(floor_x % GRID);
	int x1 = int((x0 + 1) % GRID);
	int y0 = int(floor_y % GRID);
	int y1 = int((y0 + 1) % GRID);
	int z0 = int(floor_z % GRID);
	int z1 = int((z0 + 1) % GRID);

	float sx = smoothstep(0.0f, 1.0f, dist_x);
	float sy = smoothstep(0.0f, 1.0f, dist_y);
	float sz = smoothstep(0.0f, 1.0f, dist_z);

	glm::vec3 g000 = g[p[p[p[x0] + y0] + z0]];
	glm::vec3 g100 = g[p[p[p[x1] + y0] + z0]];
	glm::vec3 g010 = g[p[p[p[x0] + y1] + z0]];
	glm::vec3 g110 = g[p[p[p[x1] + y1] + z0]];
	glm::vec3 g001 = g[p[p[p[x0] + y0] + z1]];
	glm::vec3 g101 = g[p[p[p[x1] + y0] + z1]];
	glm::vec3 g011 = g[p[p[p[x0] + y1] + z1]];
	glm::vec3 g111 = g[p[p[p[x1] + y1] + z1]];

	float c000 = glm::dot(g000, glm::normalize(glm::vec3(dist_x, dist_y, dist_z)));
	float c100 = glm::dot(g100, glm::normalize(glm::vec3(inv_dist_x, dist_y, dist_z)));
	float c010 = glm::dot(g010, glm::normalize(glm::vec3(dist_x, inv_dist_y, dist_z)));
	float c110 = glm::dot(g110, glm::normalize(glm::vec3(inv_dist_x, inv_dist_y, dist_z)));
	float c001 = glm::dot(g001, glm::normalize(glm::vec3(dist_x, dist_y, inv_dist_z)));
	float c101 = glm::dot(g101, glm::normalize(glm::vec3(inv_dist_x, dist_y, inv_dist_z)));
	float c011 = glm::dot(g011, glm::normalize(glm::vec3(dist_x, inv_dist_y, inv_dist_z)));
	float c111 = glm::dot(g111, glm::normalize(glm::vec3(inv_dist_x, inv_dist_y, inv_dist_z)));
	
	float nx00 = lerp(c000, c100, sx);
	float nx10 = lerp(c010, c110, sx);
	float nx01 = lerp(c001, c101, sx);
	float nx11 = lerp(c011, c111, sx);
	float ny0 = lerp(nx00, nx10, sy);
	float ny1 = lerp(nx01, nx11, sy);

	return 0.5 + 0.5 * lerp(ny0, ny1, sz);
}
