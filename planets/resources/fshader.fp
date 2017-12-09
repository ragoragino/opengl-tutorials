#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;

struct DirLight {
	vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct CLight {
	float constant;
	float linear;
	float quadratic;
	float inner_cutoff;
	float outer_cutoff;

	vec3 position;
	vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform DirLight dirlight;  
uniform CLight conelight; 

vec3 DirectionalLight(DirLight light, vec3 viewpos, vec3 fragpos, vec3 normal);
vec3 ConeLight(CLight light, vec3 viewpos, vec3 fragpos, vec3 normal);

void main()
{   
	// vec3 light = vec3(0.0);
	// light += DirectionalLight(dirlight, viewPos, FragPos, Normal);
	// light += ConeLight(conelight, viewPos, FragPos, Normal);
	FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
/*
 // Directional Light
vec3 DirectionalLight(DirLight light, vec3 viewpos, vec3 fragpos, vec3 normal)
{	
    vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-light.direction);

	// diffuse 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = texture(texture_diffuse1, TexCoords).rgb * diff * light.diffuse;

	// specular
	vec3 viewDir = normalize(viewpos - fragpos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
	vec3 specular = texture(texture_diffuse1, TexCoords).rgb * spec * light.specular;  

	// ambient
	vec3 ambient = texture(texture_diffuse1, TexCoords).rgb * light.ambient;
          
	return specular + ambient + diffuse; 
}

vec3 ConeLight(CLight light,  vec3 viewpos, vec3 fragpos, vec3 normal)
{
	float distance = length(light.position - fragpos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
  	
    vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragpos);
    float theta = dot(lightDir, -normalize(light.direction));
	float soft = clamp((theta - light.outer_cutoff) / (light.inner_cutoff - light.outer_cutoff), 0.0, 1.0);

	// diffuse 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = texture(texture_diffuse1, TexCoords).rgb * diff * light.diffuse;
	diffuse *= attenuation * soft;

	// specular
	vec3 viewDir = normalize(viewpos - fragpos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
	vec3 specular = texture(texture_diffuse1, TexCoords).rgb * spec * light.specular;  
	specular *= attenuation * soft;

	return diffuse; 
}
*/