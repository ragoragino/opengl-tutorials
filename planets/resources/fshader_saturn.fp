#version 330 core
# define SIZE 512
# define GRID 256
# define AMPLITUDE_MULT 0.5
# define FREQUENCY_MULT 2.0
# define AMPLITUDE 1.0
# define FREQUENCY 1.0
# define NUM_LAYERS 5
# define OFFSET_SIZE 27

out vec4 FragColor;

layout (std140) uniform DirLight
{
    vec3 ambient;
    vec3 diffuse;
};

in vec3 VerCoords;
in vec3 Normal;
in vec3 Direction;
uniform vec3 viewPos;

uniform vec3 planetCol;
uniform int p[SIZE];
uniform float r[GRID];

float noise(float in_x, float in_y)
{
	float x = in_x - int(in_x);
	float y = in_y - int(in_y);

	int floor_x = int((x * 0.5f + 0.5f) * GRID);
	int floor_y = int((y * 0.5f + 0.5f) * GRID);

	float dist_x = (x * 0.5f + 0.5f) * GRID - floor_x;
	float dist_y = (y * 0.5f + 0.5f) * GRID - floor_y;

	int rx0 = int(mod(floor_x, GRID));
	int rx1 = int(mod(rx0 + 1, GRID));
	int ry0 = int(mod(floor_y, GRID));
	int ry1 = int(mod(ry0 + 1, GRID));

	float c00 = r[p[p[rx0] + ry0]];
	float c10 = r[p[p[rx1] + ry0]];
	float c01 = r[p[p[rx0] + ry1]];
	float c11 = r[p[p[rx1] + ry1]];

	float sx = smoothstep(0.0f, 1.0f, dist_x);
	float sy = smoothstep(0.0f, 1.0f, dist_y);

	float nx0 = mix(c00, c10, sx);
	float nx1 = mix(c01, c11, sx);

	return mix(nx0, nx1, sy);
}
 
// Directional Light
vec3 DirectionalLight(vec3 direct, vec3 normal, vec3 obj_col)
{	
    vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-direct);

	// diffuse 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse_obj = obj_col * diff * diffuse;

	// ambient
	vec3 ambient_obj = obj_col * ambient;

	return ambient_obj + diffuse_obj; 
}

void main()
{
	
	float frac_noise_index = 0.0f;
	float ampl = 1.0f;
	float freq = 1.0f;
	float ampl_mult = 0.5f;
	float freq_mult = 1.2f;
	vec3 frac_vec = VerCoords * freq;
	for(int i = 0; i != 5; ++i)
	{
		frac_noise_index += noise(frac_vec.x / 5.0f, frac_vec.z / 5.0f) * ampl;
		ampl *= ampl_mult;
		freq *= freq_mult;
		frac_vec *= freq;
	}

	float frac_noise = 0.0f;
	ampl = 0.5f;
	freq = 0.5f;
	ampl_mult = 0.35f;
	freq_mult = 1.8f;
	frac_vec = VerCoords * freq;
	for(int i = 0; i != 5; ++i)
	{
		frac_noise += noise(frac_vec.y + -0.5f + 0.05f * frac_noise_index, 0.0f) * ampl;
		ampl *= ampl_mult;
		freq *= freq_mult;
		frac_vec *= freq;
	}
	
	vec3 light = vec3(0.0f);
	light += DirectionalLight(Direction, Normal, planetCol);

	gl_FragColor = vec4(light, 1.0f) * ( - clamp(1 - frac_noise, 0.0f, 1.0f) * vec4(1.0f, 0.0f, 0.0f, 1.0f) + vec4(planetCol.x, planetCol.y, planetCol.z, 1.0f));
}


