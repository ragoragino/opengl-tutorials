#version 330 core
# define SIZE 1024
# define GRID 256
# define OFFSET_SIZE 27

out vec4 FragColor;

in vec3 Normal;
in vec3 Direction;

layout (std140) uniform DirLight
{
    vec3 ambient;
    vec3 diffuse;
};

uniform vec3 planetCol;
uniform samplerCube shadow_texture;
uniform float far_plane;
uniform vec3 sampleOffsetDirections[OFFSET_SIZE];


// Point Light
vec3 PointLight(vec3 direct, vec3 normal, vec3 obj_col)
{	
    vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-direct);

	// diffuse 
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse_obj = obj_col * diff * diffuse;

	// ambient
	vec3 ambient_obj = obj_col * ambient;

	// shadow
	float currentDepth = length(direct);
    float bias = 0.05f;
	float shadow = 0.0f;
	float offset = 0.001f;
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
	vec3 light = vec3(0.0f);
	light += PointLight(Direction, Normal, planetCol);

	gl_FragColor = vec4(light, 1.0f);
}

