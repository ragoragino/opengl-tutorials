#pragma once
#include "Header.h"
#include "Shader.h"
#include "Camera.h"

class Planet
{
public:
	Planet(float distance, float speed, glm::vec3 scale, glm::vec3 color, float rotation_speed, float angle, int length);

	virtual void render(Shader& shader, float currentFrame, Camera& camera);

	float distance, sun_rotation_speed,  own_rotation_speed, angle, rotation_speed_angle;
	glm::vec3 scale, color;

	int length;
	float x, z;
	glm::vec3 rotate_vec;
};


Planet::Planet(float distance, float speed, glm::vec3 scale, glm::vec3 color, float own_rotation_speed, float angle, int length) :
	distance{ distance },
	sun_rotation_speed{ speed },
	scale{ scale },
	color{ color },
	own_rotation_speed{ own_rotation_speed },
	angle{ angle },
	x{ 0.0f },
	z{ 0.0f },
	rotate_vec{ 0.0f },
	length{ length }
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

	// Rotate around the Sun
	this->x = distance * glm::sin(rotation_speed_angle * currentFrame);
	this->z = -distance * glm::cos(rotation_speed_angle * currentFrame);

	// Get the vector on which to rotate the planet towards the Sun
	this->rotate_vec = glm::cross(glm::vec3(x, 0.0f, z), glm::vec3(0.0f, 1.0f, 0.0f));
	
	// Translate, rotate towards the Sun, around own axis and scale
	glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(x, 0.0f, z));
	model = glm::rotate(model, glm::radians(angle), rotate_vec);
	model = glm::rotate(model, (float)(-2.0f * M_PI * currentFrame / own_rotation_speed), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, scale);

	shader.set("model", model);
	shader.set("viewPos", camera.Position);

	glDrawArrays(GL_TRIANGLES, 0, 36 * length * length);
}


class Moon : public Planet
{
public:
	Moon(Planet* planet, float distance, float speed, glm::vec3 scale, glm::vec3 color, float own_rotation_speed, float angle, int length) :
		planet{ planet }, Planet{ distance, speed, scale, color, own_rotation_speed, angle, length } {};

	void render(Shader& shader, float currentFrame, Camera& camera);

	Planet* planet;	
};


inline void Moon::render(Shader& shader, float currentFrame, Camera& camera)
{
	shader.use();

	// Rotate around the Sun and the Planet
	this->x = distance * glm::sin(rotation_speed_angle * currentFrame) + planet->x;
	this->z = -distance * glm::cos(rotation_speed_angle * currentFrame) + planet->z;

	// Get the vector on which to rotate the moon towards the Sun
	this->rotate_vec = glm::cross(glm::vec3(x, 0.0f, z), glm::vec3(0.0f, 1.0f, 0.0f));

	// Translate, rotate towards the Sun, around own axis and scale
	glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(x, 0.0f, z));
	model = glm::rotate(model, glm::radians(angle), rotate_vec);
	model = glm::rotate(model, (float)(-2.0f * M_PI * currentFrame / own_rotation_speed), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, scale);

	shader.set("model", model);
	shader.set("viewPos", camera.Position);

	glDrawArrays(GL_TRIANGLES, 0, 36 * length * length);
}