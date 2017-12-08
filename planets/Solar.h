#pragma once
#define _USE_MATH_DEFINES 
#include "math.h"

const float earth_distance = 10.0f;
const float moon_distance = 2.0f; // distance of Moon from Earth
const float saturn_distance = 20.0f;
const float meteor_distance = 25.0f;
const float earth_speed = 36.5f;
const float moon_speed = 2.7f;
const float saturn_speed = 100.0f;
const float earth_dispos = 2 * M_PI / earth_speed; // angular change for one second in the rotation of Earth around the Sun
const float moon_dispos = 2 * M_PI / moon_speed; // angular change for one second in the rotation of Moon around Earth
const float saturn_dispos = 2 * M_PI / saturn_speed; // angular change for one second in the rotation of Saturn around the Sun

// INITIAL POSITIONS
const glm::vec3 sun_pos = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 earth_pos = glm::vec3(0.0f, 0.0f, -earth_distance);
const glm::vec3 moon_pos = glm::vec3(moon_distance, 0.0f, -earth_distance);
const glm::vec3 saturn_pos = glm::vec3(0.0f, 0.0f, -saturn_distance);
const glm::vec3 meteor_pos = glm::vec3(0.0f, 0.0f, -meteor_distance);

// SCALES
const glm::vec3 sun_scale = 4.0f * glm::vec3(1.0f);
const glm::vec3 earth_scale = 1.0f * glm::vec3(1.0f);
const glm::vec3 moon_scale = 0.2f * glm::vec3(1.0f);
const glm::vec3 saturn_scale = 2.0f * glm::vec3(1.0f);
const glm::vec3 saturn_ring_scale = 3.5f * glm::vec3(1.0f);
const glm::vec3 meteor_scale = 2.0f * glm::vec3(1.0f);

// COLORS
glm::vec3 sun_color = glm::vec3(252.0, 212.0f, 64.0f) / 256.0f;
glm::vec3 earth_color = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 moon_color = glm::vec3(0.5f, 0.5f, 0.5f);
glm::vec3 saturn_color = glm::vec3(1.000f, 0.871f, 0.678f);
glm::vec3 saturn_ring_color = glm::vec3(0.804f, 0.522f, 0.247f);
glm::vec3 meteor_color = glm::vec3(0.545f, 0.271f, 0.075f);

// ROTATIONS
float saturn_angle = 15.0f;