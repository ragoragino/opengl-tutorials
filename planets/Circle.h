#pragma once
#define _USE_MATH_DEFINES 
#include "math.h"

float * circle(float size = 2.0f)
{
	float * circle = new float[36]
	{
		-size / 2, 0.0f, size / 2, 0.0f, 1.0f, 0.0f,
		-size / 2, 0.0f, -size / 2, 0.0f, 1.0f, 0.0f,
		size / 2, 0.0f, size / 2, 0.0f, 1.0f, 0.0f,

		-size / 2, 0.0f, -size / 2, 0.0f, 1.0f, 0.0f,
		size / 2, 0.0f, size / 2, 0.0f, 1.0f, 0.0f,
		size / 2, 0.0f, -size / 2, 0.0f, 1.0f, 0.0f
	};

	return circle;
}