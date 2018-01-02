#version 330 core
# define GRID 256
# define AMPLITUDE_MULT 0.5
# define FREQUENCY_MULT 2.0
# define AMPLITUDE 1.0
# define FREQUENCY 1.0
# define NUM_LAYERS 5
# define OFFSET_SIZE 27

out vec4 FragColor;

in vec3 VerCoords;
in vec3 Normal;
in vec3 Direction;

uniform vec3 planetCol;
uniform int p[GRID];
uniform float r[GRID];
uniform vec3 sampleOffsetDirections[OFFSET_SIZE];
uniform samplerCube shadow_texture;
uniform float far_plane;

layout (std140) uniform DirLight
{
    vec3 ambient;
    vec3 diffuse;
};

float noise(float in_x)
{
	float x = in_x - int(in_x);

	int floor_x = int((x * 0.5f + 0.5f) * GRID);

	float dist_x = (x * 0.5f + 0.5f) * GRID - floor_x;

	int rx0 = int(mod(floor_x, GRID));
	int rx1 = int(mod(rx0 + 1, GRID));

	float c0 = r[p[rx0]];
	float c1 = r[p[rx1]];

	float sx = smoothstep(0.0f, 1.0f, dist_x);

	return mix(c0, c1, sx);
}

// Point Light
vec3 DirectionalLight(vec3 direct, vec3 normal, vec3 obj_col)
{	
    vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-direct);

	// diffuse 
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse_obj = obj_col * diff * diffuse;

	// ambient
	vec3 ambient_obj = obj_col * (ambient + 0.2f); // manual adjustment to lighten the ring a bit

	// shadow
	float currentDepth = length(direct);
    float bias = 0.05f;
	float shadow = 0.0f;
	float offset = 0.001f;
	float closestDepth;
	for(int i = 0; i < OFFSET_SIZE; ++i)
	{
		closestDepth = texture(shadow_texture, direct + sampleOffsetDirections[i] * offset).r;
		closestDepth *= far_plane;
		shadow += currentDepth - bias > closestDepth ? 1.0f : 0.0f;
	}    

	shadow /= OFFSET_SIZE;
          
	return  ambient_obj + (1.0f - shadow) * diffuse_obj; 
}

void main()
{
	float distance = VerCoords.x * VerCoords.x + VerCoords.z * VerCoords.z;

	float frac_noise = 0.0f;
	float ampl = 0.5f;
	float freq = 1.0f;
	float ampl_mult = 0.1f;
	float freq_mult = 1.5f;
	float frac_vec = distance * freq;
	for(int i = 0; i != 5; ++i)
	{
		frac_noise += noise(frac_vec) * ampl;
		ampl *= ampl_mult;
		freq *= freq_mult;
		frac_vec *= freq;
	}

	vec3 light = vec3(0.0f);
	light += DirectionalLight(Direction, Normal, planetCol);

	if (distance < 1.0f && distance > 0.5f)
	{
		gl_FragColor = vec4(light, clamp(frac_noise, 0.0f, 1.0f)); 
	}
	else
	{
		gl_FragColor = vec4(0.0f); 
	}
}