#pragma once
#define _USE_MATH_DEFINES 
#include "math.h"

float * square(float size = 2.0f)
{
	float * square = new float[36]
	{
		-size / 2, 0.0f, size / 2, 0.0f, 1.0f, 0.0f,
		-size / 2, 0.0f, -size / 2, 0.0f, 1.0f, 0.0f,
		size / 2, 0.0f, size / 2, 0.0f, 1.0f, 0.0f,

		-size / 2, 0.0f, -size / 2, 0.0f, 1.0f, 0.0f,
		size / 2, 0.0f, size / 2, 0.0f, 1.0f, 0.0f,
		size / 2, 0.0f, -size / 2, 0.0f, 1.0f, 0.0f
	};

	return square;
}