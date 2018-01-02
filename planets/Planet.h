#pragma once
#include "Header.h"
#include "Shader.h"
#include "Camera.h"

class Planet
{
public:
	Planet(float in_distance, float in_speed, glm::vec3 in_scale, glm::vec3 in_color, float in_rotation_speed, float in_angle, int in_length);

	virtual void render(Shader& shader, float currentFrame, Camera& camera);

	float distance, sun_rotation_speed,  own_rotation_speed, angle, rotation_speed_angle;
	glm::vec3 scale, color;

	int length;
	float x, z;
	glm::vec3 rotate_vec;
};


Planet::Planet(float in_distance, float in_speed, glm::vec3 in_scale, glm::vec3 in_color, float in_own_rotation_speed, float in_angle, int in_length) :
	distance(in_distance),
	sun_rotation_speed(in_speed),
	scale(in_scale),
	color(in_color),
	own_rotation_speed(in_own_rotation_speed),
	angle(in_angle),
	x(0.0f),
	z(0.0f),
	rotate_vec(0.0f),
	length(in_length)
{
	// Exclude division by zero or negative speed
	if (sun_rotation_speed > 0.01)
	{
		rotation_speed_angle = 2.0f * (float)M_PI / sun_rotation_speed;
	}
	else
	{
		rotation_speed_angle = 0.0f;
	}

}


inline void Planet::render(Shader& shader, float currentFrame, Camera& camera)
{
	shader.use();

	this->x = distance * glm::sin(rotation_speed_angle * currentFrame);
	this->z = -distance * glm::cos(rotation_speed_angle * currentFrame);

	// Get the vector on which to rotate the planet
	this->rotate_vec = glm::cross(glm::vec3(x, 0.0f, z), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(x, 0.0f, z));
	model = glm::rotate(model, glm::radians(angle), rotate_vec);
	model = glm::scale(model, scale);
	model = glm::rotate(model, (float)(-2.0f * M_PI * currentFrame / own_rotation_speed), glm::vec3(0.0f, 1.0f, 0.0f)); // Axis rotation

	shader.set("model", model);
	shader.set("viewPos", camera.Position);

	glDrawArrays(GL_TRIANGLES, 0, 36 * length * length);
}


class Moon : public Planet
{
public:
	Moon(Planet* in_planet, float in_distance, float in_speed, glm::vec3 in_scale, glm::vec3 in_color, float in_own_rotation_speed, float in_angle, int length) :
		planet(in_planet), Planet(in_distance, in_speed, in_scale, in_color, in_own_rotation_speed, in_angle, length) {};

	void render(Shader& shader, float currentFrame, Camera& camera);

	Planet* planet;	
};


inline void Moon::render(Shader& shader, float currentFrame, Camera& camera)
{
	shader.use();

	this->x = distance * glm::sin(rotation_speed_angle * currentFrame) + planet->x;
	this->z = -distance * glm::cos(rotation_speed_angle * currentFrame) + planet->z;

	// Get the vector on which to rotate the moon
	this->rotate_vec = glm::cross(glm::vec3(x, 0.0f, z), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(x, 0.0f, z));
	model = glm::rotate(model, glm::radians(angle), rotate_vec);
	model = glm::scale(model, scale);
	model = glm::rotate(model, (float)(-2.0f * M_PI * currentFrame / own_rotation_speed), glm::vec3(0.0f, 1.0f, 0.0f)); // Axis rotation

	shader.set("model", model);
	shader.set("viewPos", camera.Position);

	glDrawArrays(GL_TRIANGLES, 0, 36 * length * length);
}