#pragma once
#include "Header.h"

float * sphere(int n, float size = 2.0f)
{
	float base_sq[] = {
		-size / 2.0f, -size / 2.0f, size / 2.0f,
		-size / 2.0f + size / n, -size / 2.0f, size / 2.0f,
		-size / 2.0f, -size / 2.0f + size / n, size / 2.0f,

		-size / 2.0f, -size / 2.0f + size / n, size / 2.0f,
		-size / 2.0f + size / n, -size / 2.0f, size / 2.0f,
		-size / 2.0f + size / n, -size / 2.0f + size / n, size / 2.0f,
	};
	
	float * square = new float[6 * n * n * 18];
	int base_length = 18;

	// Front side of the square
	for (int i = 0; i != n; ++i)
	{
		for (int j = 0; j != n; ++j)
		{
			for (int k = 0; k < base_length; k += 3)
			{
				square[base_length * n * i + base_length * j + k] = base_sq[k] + j * size / n;
				square[base_length * n * i + base_length * j + k + 1] = base_sq[k + 1] + i * size / n;
				square[base_length * n * i + base_length * j + k + 2] = size / 2;
			}
		}
	}

	float coef_11 = 0.0f;
	float coef_12 = 0.0f;
	float coef_13 = 0.0f;
	float coef_21 = 0.0f;
	float coef_22 = 0.0f;
	float coef_23 = 0.0f;
	float coef_31 = 0.0f;
	float coef_32 = 0.0f;
	float coef_33 = 0.0f;

	int side_offset = 0;

	// Rotation by x axis -> 90, 180 and 270 degress
	for (int i = 1; i != 4; ++i)
	{
		side_offset = i * base_length * n * n;

		coef_22 = (float)cos(i * M_PI * 0.5f);
		coef_32 = (float)sin(i * M_PI * 0.5f);
		coef_23 = (float)-sin(i * M_PI * 0.5f);
		coef_33 = (float)cos(i * M_PI * 0.5f);

		for (int j = 0; j < base_length * n * n; j += 3)
		{
			square[side_offset + j] = square[j];
			square[side_offset + j + 1] = square[j + 1] * coef_22 + square[j + 2] * coef_23;
			square[side_offset + j + 2] = square[j + 1] * coef_32 + square[j + 2] * coef_33;
		}
	}

	// Rotation by y axis - > 90 degress
	coef_11 = (float)cos(M_PI * 0.5f);
	coef_31 = (float)-sin(M_PI * 0.5f);
	coef_13 = (float)sin(M_PI * 0.5f);
	coef_33 = (float)cos(M_PI * 0.5f);

	side_offset = 4 * base_length * n * n;

	for (int j = 0; j < base_length * n * n; j += 3)
	{
		square[side_offset + j] = square[j] * coef_11 + square[j + 2] * coef_13;
		square[side_offset + j + 1] = square[j + 1];
		square[side_offset + j + 2] = square[j] * coef_31 + square[j + 2] * coef_33;
	}

	// Rotation by y axis - > 270 degress
	coef_11 = (float)cos(3.0f * M_PI * 0.5f);
	coef_31 = (float)-sin(3.0 * M_PI * 0.5f);
	coef_13 = (float)sin(3.0f * M_PI * 0.5f);
	coef_33 = (float)cos(3.0f * M_PI * 0.5f);

	side_offset = 5 * base_length * n * n;

	for (int j = 0; j < base_length * n * n; j += 3)
	{
		square[side_offset + j] = square[j] * coef_11 + square[j + 2] * coef_13;
		square[side_offset + j + 1] = square[j + 1];
		square[side_offset + j + 2] = square[j] * coef_31 + square[j + 2] * coef_33;
	}

	// Cube to sphere mapping -> source: http://mathproofs.blogspot.cz/2005/07/mapping-cube-to-sphere.html
	float tmp_x = 0.0f;
	float tmp_y = 0.0f;
	float tmp_z = 0.0f;

	for (int i = 0; i < 6 * n * n * base_length; i += 3)
	{
		tmp_x = (float)pow(1.0 - 0.5 * square[i + 1] * square[i + 1] - 0.5 * square[i + 2] * square[i + 2] + 0.33333 * square[i + 1] * square[i + 1] * square[i + 2] * square[i + 2], 0.5);
		tmp_y = (float)pow(1.0 - 0.5 * square[i + 2] * square[i + 2] - 0.5 * square[i] * square[i] + 0.33333 * square[i] * square[i] * square[i + 2] * square[i + 2], 0.5);
		tmp_z = (float)pow(1.0 - 0.5 * square[i + 1] * square[i + 1] - 0.5 * square[i] * square[i] + 0.33333 * square[i + 1] * square[i + 1] * square[i] * square[i], 0.5);

		square[i] *= tmp_x;
		square[i + 1] *= tmp_y;
		square[i + 2] *= tmp_z;
	}

	return square;
}