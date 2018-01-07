#pragma once
#include "Camera.h"
#include "Planet.h"
#include "Snapshot.h"

// Camera object
Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

// Variables for capturing mouse movements
float lastX = 400, lastY = 300;
bool firstMouse = true;

// Variables for capturing time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Screen parameters and initial screen position
uint32_t screen_width = 1200, screen_height = 800;
uint32_t screen_pos_x = 200, screen_pos_y = 200;

// Snapshot class instance for taking snapshots
Snapshot snapshot(screen_width, screen_height); 

