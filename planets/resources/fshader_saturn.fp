#version 330 core
# define GRID 256
# define AMPLITUDE_MULT 0.5
# define FREQUENCY_MULT 2.0
# define AMPLITUDE 1.0
# define FREQUENCY 1.0
# define NUM_LAYERS 5

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
 
// Directional Light
vec3 DirectionalLight(vec3 direct, vec3 normal, vec3 obj_col)
{	
    vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-direct);

	// diffuse 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = obj_col * diff * diffuse;

	// ambient
	vec3 ambient = obj_col * ambient;
          
	return ambient + diffuse; 
}

void main()
{
	float frac_noise = 0.0f;
	float ampl = 0.5f;
	float freq = 0.5f;
	float ampl_mult = 0.35f;
	float freq_mult = 1.8f;
	vec3 frac_vec = VerCoords * freq;
	for(int i = 0; i != 5; ++i)
	{
		frac_noise += noise(frac_vec.y) * ampl;
		ampl *= ampl_mult;
		freq *= freq_mult;
		frac_vec *= freq;
	}
	
	vec3 light = vec3(0.0f);
	light += DirectionalLight(Direction, Normal, planetCol);

	gl_FragColor = vec4(light, 1.0f) * ( - clamp(1 - frac_noise, 0.0f, 1.0f) * vec4(1.0f, 0.0f, 0.0f, 1.0f) + vec4(planetCol.x, planetCol.y, planetCol.z, 1.0f)); 
}


