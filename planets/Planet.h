#pragma once
#define _USE_MATH_DEFINES
#include "Shader.h"
#include "math.h"

class Planet
{
public:
	Planet(float in_distance, float in_speed, float in_scale, float in_color, float in_init_position, float in_rotation_speed, float in_angle);

	void render(Shader shader);

	float distance, init_position, scale, sun_rotation_speed,  own_rotation_speed, angle, color, rotation_speed_angle;

private:
		
};


Planet::Planet(float in_distance, float in_speed, float in_scale, float in_color, float in_init_position, float in_rotation_speed, float in_angle) : 
	distance(in_distance),
	sun_rotation_speed(in_speed),
	scale(in_scale),
	color(in_color),
	init_position(in_init_position),
	own_rotation_speed(in_rotation_speed),
	angle(in_angle)
{
	rotation_speed_angle = 2 * M_PI / sun_rotation_speed;
}


void Planet::render(Shader shader)
{
		
}
