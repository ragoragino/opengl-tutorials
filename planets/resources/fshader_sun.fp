#version 330 core
# define SIZE 1024
# define GRID 256

out vec4 FragColor;

in vec3 VerCoords;

uniform vec3 planetCol;
uniform int p[SIZE];
uniform float r[GRID];
uniform float time;

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

	int rx0 = int(mod(floor_x, 256)); 
	int rx1 = int(mod(rx0 + 1, GRID));
	int ry0 = int(mod(floor_y, GRID));
	int ry1 = int(mod(ry0 + 1, GRID));
	int rz0 = int(mod(floor_z, GRID));
	int rz1 = int(mod(rz0 + 1, GRID));
	int rw0 = int(mod(floor_w, GRID));
	int rw1 = int(mod(rw0 + 1, GRID));

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

	float nx000 = mix(c0000, c1000, sx);
	float nx100 = mix(c0100, c1100, sx);
	float nx010 = mix(c0010, c1010, sx);
	float nx110 = mix(c0110, c1110, sx);
	float nx001 = mix(c0001, c1001, sx);
	float nx101 = mix(c0101, c1101, sx);
	float nx011 = mix(c0011, c1011, sx);
	float nx111 = mix(c0111, c1111, sx);

	float ny00 = mix(nx000, nx100, sy);
	float ny10 = mix(nx010, nx110, sy);
	float ny01 = mix(nx001, nx101, sy);
	float ny11 = mix(nx011, nx111, sy);

	float nz0 = mix(ny00, ny10, sz);
	float nz1 = mix(ny01, ny11, sz);

	return mix(nz0, nz1, sw);
}

void main()
{
	float frac_noise = 0.0f;
	float ampl = 0.6f;
	float freq = 0.1f;
	float ampl_mult = 0.5f;
	float freq_mult = 0.2f;
	vec3 frac_vec = VerCoords * freq;
	for(int i = 0; i != 5; ++i)
	{
		frac_noise += noise(frac_vec.x, frac_vec.y, frac_vec.z, time / 300.0f) * ampl;
		ampl *= ampl_mult;
		freq *= freq_mult;
		frac_vec *= freq;
	}

	frac_noise = frac_noise * 0.2f + 0.6f;

	gl_FragColor = vec4(frac_noise * planetCol, 1.0); 
}

