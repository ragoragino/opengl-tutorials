#version 330 core
# define SIZE 768
# define GRID 256
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
uniform int p[SIZE];
uniform float r[GRID];
uniform vec3 sampleOffsetDirections[OFFSET_SIZE];
uniform samplerCube shadow_texture;
uniform float far_plane;

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

 
// Point Light
vec3 DirectionalLight(vec3 direct, vec3 normal, vec3 obj_col)
{	
    vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-Direction);

	// diffuse 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse_obj = obj_col * diff * diffuse;

	// ambient
	vec3 ambient_obj = obj_col * ambient;

	// shadow
	float currentDepth = length(direct);
    float bias = 0.05f;
	float shadow = 0.0f;
	float offset = 0.01f;
	float closestDepth;
	for(int i = 0; i < OFFSET_SIZE; ++i)
	{
		closestDepth = texture(shadow_texture, Direction + sampleOffsetDirections[i] * offset).r;
		closestDepth *= far_plane;
		shadow += currentDepth - bias > closestDepth ? 1.0f : 0.0f;
	}    

	shadow /= OFFSET_SIZE;

	return ambient_obj + (1.0f - shadow) * diffuse_obj; 
}

void main()
{
	float frac_noise = 0.0f;
	float ampl = 0.6f;
	float freq = 0.01f;
	float ampl_mult = 0.5f;
	float freq_mult = 0.1f;
	vec3 frac_vec = VerCoords * freq;
	for(int i = 0; i != 5; ++i)
	{
		frac_noise += noise(frac_vec.x, frac_vec.y, frac_vec.z) * ampl;
		ampl *= ampl_mult;
		freq *= freq_mult;
		frac_vec *= freq;
	}

	float clouds = 0.0f;
	ampl = 0.4f;
	freq = 0.03f;
	ampl_mult = 0.2f;
	freq_mult = 0.1f;
	frac_vec = VerCoords * freq;
	for(int i = 0; i != 5; ++i)
	{
		clouds += noise(frac_vec.x, frac_vec.y, frac_vec.z) * ampl;
		ampl *= ampl_mult;
		freq *= freq_mult;
		frac_vec *= freq;
	}
	
	vec3 light = vec3(0.0f);

	// Mix green and blue
	vec3 EarthColor = mix(vec3(0.0, 1.0, 0.0), vec3(0.1, 0.1, 1.0), clamp(frac_noise, 0.0, 1.0));
		
	// Add white clouds to the atmosphere
	EarthColor = mix(EarthColor, vec3(1.0), clamp(clouds, 0.0, 1.0));

	light += DirectionalLight(Direction, Normal, EarthColor);

	gl_FragColor = vec4(light, 1.0);
}
