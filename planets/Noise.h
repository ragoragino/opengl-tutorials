# pragma once
# define SIZE 1024
# define GRID 256

/*
Arrays and initializer for noise functions.
The implementation is also in fragment shaders -> this part is for sanity checks.
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

static float r[GRID]; // Random numbers array: (0.0, 1.0)

void init_buffers()
{
	for (int i = 0; i != GRID * 2; ++i)
	{
		int index = int(rand() % GRID);
		p[i + GRID] = p[index];
	}

	for (int i = 0; i != GRID; ++i)
	{
		r[i] = (float)rand() / (float)RAND_MAX;
	}
}

// Implementation of the value noise function

template<typename T>
T smoothstep(T edge0, T edge1, T x)
{
	T t = (x - edge0) / (edge1 - edge0);
	t > 1.0f ? 1.0f : (t < 0.0f ? 0.0f : t);
	return t * t * (3.0f - 2.0f * t);
}

template<typename T>
T lerp(T a, T b, T t)
{
	return a * (1 - t) + b * t;
}

// 1D Noise
float noise(float in_x)
{
	float x = in_x - int(in_x);

	int floor_x = int((x * 0.5f + 0.5f) * GRID);

	float dist_x = (x * 0.5f + 0.5f) * GRID - floor_x;

	int rx0 = int(floor_x % GRID);
	int rx1 = int((rx0 + 1) % GRID);

	float c000 = r[p[rx0]];
	float c100 = r[p[rx1]];

	float sx = smoothstep(0.0f, 1.0f, dist_x);

	return lerp(c000, c100, sx);
}

// 2D Noise
float noise(float in_x, float in_y)
{
	float x = in_x - int(in_x);
	float y = in_y - int(in_y);

	int floor_x = int((x * 0.5f + 0.5f) * GRID);
	int floor_y = int((y * 0.5f + 0.5f) * GRID);

	float dist_x = (x * 0.5f + 0.5f) * GRID - floor_x;
	float dist_y = (y * 0.5f + 0.5f) * GRID - floor_y;

	int rx0 = int(floor_x % GRID);
	int rx1 = int((rx0 + 1) % GRID);
	int ry0 = int(floor_y % GRID);
	int ry1 = int((ry0 + 1) % GRID);

	float c00 = r[p[p[rx0] + ry0]];
	float c10 = r[p[p[rx1] + ry0]];
	float c01 = r[p[p[rx0] + ry1]];
	float c11 = r[p[p[rx1] + ry1]];

	float sx = smoothstep(0.0f, 1.0f, dist_x);
	float sy = smoothstep(0.0f, 1.0f, dist_y);

	float nx0 = lerp(c00, c10, sx);
	float nx1 = lerp(c01, c11, sx);

	return lerp(nx0, nx1, sy);
}

// 3D Noise
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

	int rx0 = int(floor_x % GRID);
	int rx1 = int((rx0 + 1) % GRID);
	int ry0 = int(floor_y % GRID);
	int ry1 = int((ry0 + 1) % GRID);
	int rz0 = int((floor_z) % GRID);
	int rz1 = int((rz0 + 1) % GRID);

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

	float nx00 = lerp(c000, c100, sx);
	float nx10 = lerp(c010, c110, sx);
	float nx01 = lerp(c001, c101, sx);
	float nx11 = lerp(c011, c111, sx);
	float ny0 = lerp(nx00, nx10, sy);
	float ny1 = lerp(nx01, nx11, sy);

	return lerp(ny0, ny1, sz);
}

// 4D noise
float noise(float in_x, float in_y, float in_z, float in_w)
{
	float x = in_x - int(in_x);
	float y = in_y - int(in_y);
	float z = in_z - int(in_z);
	float w = in_w - int(in_w);

	int floor_x = int((x * 0.5f + 0.5f) * GRID);
	int floor_y = int((y * 0.5f + 0.5f) * GRID);
	int floor_z = int((z * 0.5f + 0.5f) * GRID);
	int floor_w = int((w * 0.5f + 0.5f) * GRID);

	float dist_x = (x * 0.5f + 0.5f) * GRID - floor_x;
	float dist_y = (y * 0.5f + 0.5f) * GRID - floor_y;
	float dist_z = (z * 0.5f + 0.5f) * GRID - floor_z;
	float dist_w = (w * 0.5f + 0.5f) * GRID - floor_w;

	int rx0 = int(floor_x % GRID);
	int rx1 = int((rx0 + 1) % GRID);
	int ry0 = int(floor_y % GRID);
	int ry1 = int((ry0 + 1) % GRID);
	int rz0 = int((floor_z) % GRID);
	int rz1 = int((rz0 + 1) % GRID);
	int rw0 = int((floor_w) % GRID);
	int rw1 = int((rw0 + 1) % GRID);

	float c0000 = r[p[p[p[p[rx0] + ry0] + rz0] + rw0]];
	float c1000 = r[p[p[p[p[rx1] + ry0] + rz0] + rw0]];
	float c0100 = r[p[p[p[p[rx0] + ry1] + rz0] + rw0]];
	float c1100 = r[p[p[p[p[rx1] + ry1] + rz0] + rw0]];
	float c0010 = r[p[p[p[p[rx0] + ry0] + rz1] + rw0]];
	float c1010 = r[p[p[p[p[rx1] + ry0] + rz1] + rw0]];
	float c0110 = r[p[p[p[p[rx0] + ry1] + rz1] + rw0]];
	float c1110 = r[p[p[p[p[rx1] + ry1] + rz1] + rw0]];
	float c0001 = r[p[p[p[p[rx0] + ry0] + rz0] + rw1]];
	float c1001 = r[p[p[p[p[rx1] + ry0] + rz0] + rw1]];
	float c0101 = r[p[p[p[p[rx0] + ry1] + rz0] + rw1]];
	float c1101 = r[p[p[p[p[rx1] + ry1] + rz0] + rw1]];
	float c0011 = r[p[p[p[p[rx0] + ry0] + rz1] + rw1]];
	float c1011 = r[p[p[p[p[rx1] + ry0] + rz1] + rw1]];
	float c0111 = r[p[p[p[p[rx0] + ry1] + rz1] + rw1]];
	float c1111 = r[p[p[p[p[rx1] + ry1] + rz1] + rw1]];

	float sx = smoothstep(0.0f, 1.0f, dist_x);
	float sy = smoothstep(0.0f, 1.0f, dist_y);
	float sz = smoothstep(0.0f, 1.0f, dist_z);
	float sw = smoothstep(0.0f, 1.0f, dist_w);

	float nx000 = lerp(c0000, c1000, sx);
	float nx100 = lerp(c0100, c1100, sx);
	float nx010 = lerp(c0010, c1010, sx);
	float nx110 = lerp(c0110, c1110, sx);
	float nx001 = lerp(c0001, c1001, sx);
	float nx101 = lerp(c0101, c1101, sx);
	float nx011 = lerp(c0011, c1011, sx);
	float nx111 = lerp(c0111, c1111, sx);

	float ny00 = lerp(nx000, nx100, sy);
	float ny10 = lerp(nx010, nx110, sy);
	float ny01 = lerp(nx001, nx101, sy);
	float ny11 = lerp(nx011, nx111, sy);

	float nz0 = lerp(ny00, ny10, sz);
	float nz1 = lerp(ny01, ny11, sz);

	return lerp(nz0, nz1, sw);
}


