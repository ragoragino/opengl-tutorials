#version 330 core
out vec4 FragColor;

in vec3 VerCoords;

uniform vec3 planetCol;
uniform float time;
uniform float diameter;

void main()
{
	float distance = pow(VerCoords.x * VerCoords.x + VerCoords.y * VerCoords.y, 0.5);

	if((distance < 1.5f * diameter) && (distance > diameter))
	{
		// manual configuration of 
		gl_FragColor = vec4(planetCol, 0.1f + 1.0f - distance / (1.2f * diameter));
		//gl_FragColor = vec4(1.0f);
	}
	else
	{
		gl_FragColor = vec4(0.0f); 
	}	
	
}

