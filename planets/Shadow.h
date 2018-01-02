#pragma once
#include "Header.h"
#define OFFSET_SIZE 27

// Offset directions for sampling from shadow textures
glm::vec3 ShadowOffsetDirections[OFFSET_SIZE] = 
{
	glm::vec3(1, 1, 1), glm::vec3(1, 1, 0), glm::vec3(1, 1, -1),
	glm::vec3(1, 0, 1), glm::vec3(1, 0, 0), glm::vec3(1, 0, -1),
	glm::vec3(1, -1, 1), glm::vec3(1, -1, 0), glm::vec3(1, -1, -1),
	glm::vec3(0, 1, 1), glm::vec3(0, 1, 0), glm::vec3(0, 1, -1),
	glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1),
	glm::vec3(0, -1, 1), glm::vec3(0, -1, 0), glm::vec3(0, -1, -1),
	glm::vec3(-1, 1, 1), glm::vec3(-1, 1, 0), glm::vec3(-1, 1, -1),
	glm::vec3(-1, 0, 1), glm::vec3(-1, 0, 0), glm::vec3(-1, 0, -1),
	glm::vec3(-1, -1, 1), glm::vec3(-1, -1, 0), glm::vec3(-1, -1, -1)
};