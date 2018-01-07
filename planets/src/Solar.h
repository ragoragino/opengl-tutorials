#pragma once
#include "Header.h"

// RADIUS DISTANCES FROM THE SUN AND ROTATION SPEEDS AROUND THE SUN
const float earth_distance = 10.0f;
const float moon_distance = 2.0f; // distance of Moon from Earth
const float saturn_distance = 40.0f;
const float meteor_distance = 25.0f;
const float earth_speed = 36.5f;
const float moon_speed = 15.7f;
const float saturn_speed = 100.0f;
const float meteor_speed = 36.5f;
const float earth_dispos = 2.0f * (float)M_PI / earth_speed; // angular change for one second in the rotation of Earth around the Sun
const float moon_dispos = 2.0f * (float)M_PI / moon_speed; // angular change for one second in the rotation of Moon around the Earth
const float saturn_dispos = 2.0f * (float)M_PI / saturn_speed; // angular change for one second in the rotation of Saturn around the Sun
const float meteor_dispos = 2.0f * (float)M_PI / meteor_speed; // angular change for one second in the rotation of meteors around the Sun

// INITIAL POSITIONS
const glm::vec3 sun_pos = glm::vec3(0.0f, 0.0f, 0.0f); // SUN MUST BE POSITIONED IN THE CENTRE ! -> fragment shader dependency

// SCALES
const float sun_factor = 4.0f;
const glm::vec3 sun_scale = sun_factor * glm::vec3(1.0f);
const float earth_factor = 1.0f;
const glm::vec3 earth_scale = earth_factor * glm::vec3(1.0f);
const float moon_factor = 0.2f;
const glm::vec3 moon_scale = moon_factor * glm::vec3(1.0f);
const float saturn_factor = 2.0f;
const glm::vec3 saturn_scale = saturn_factor * glm::vec3(1.0f);
const float saturn_ring_factor = 3.5f;
const glm::vec3 saturn_ring_scale = saturn_ring_factor * glm::vec3(1.0f);
const float meteor_factor = 0.1f;
const glm::vec3 meteor_scale = meteor_factor * glm::vec3(1.0f);

// COLORS
const glm::vec3 sun_color = glm::vec3(0.9f, 0.7f, 0.2f);
const glm::vec3 earth_color = glm::vec3(0.1f, 0.8f, 0.1f);
const glm::vec3 moon_color = glm::vec3(0.5f, 0.5f, 0.5f);
const glm::vec3 saturn_color = glm::vec3(1.000f, 0.871f, 0.678f);
const glm::vec3 saturn_ring_color = glm::vec3(0.804f, 0.522f, 0.247f);
const glm::vec3 meteor_color = glm::vec3(0.6f, 0.3f, 0.0f);

// ROTATIONS SPEEDS AROUND OWN AXIS
const float earth_rotation = 5.0f;
const float saturn_rotation = 10.0f;
const float moon_rotation = 10.0f;

// ANGLES
const float saturn_angle = 15.0f;

// LIGHTS -> no specular light
const glm::vec3 sunlight_diffuse(0.6f);
const glm::vec3 sunlight_ambient(0.2f);

// SUN BLOOM
const float sun_scale_bloom_factor = 1.5f;
const glm::vec3 sun_scale_bloom = sun_factor * glm::vec3(1.0f) * sun_scale_bloom_factor;

