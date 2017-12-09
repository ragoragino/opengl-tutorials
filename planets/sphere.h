#pragma once
#define _USE_MATH_DEFINES 
#include "math.h"
#include "Header.h"

float * sphere(unsigned int n, float size = 2.0f)
{
	float base_sq[] = {
		-size / 2, -size / 2, size / 2, 0.0f, 0.0f, 1.0f,
		-size / 2 + size / n, -size / 2, size / 2, 0.0f, 0.0f, 1.0f,
		-size / 2, -size / 2 + size / n, size / 2, 0.0f, 0.0f, 1.0f,

		-size / 2, -size / 2 + size / n, size / 2, 0.0f, 0.0f, 1.0f,
		-size / 2 + size / n, -size / 2, size / 2, 0.0f, 0.0f, 1.0f,
		-size / 2 + size / n, -size / 2 + size / n, size / 2, 0.0f, 0.0f, 1.0f,
	};
	
	float * square = new float[6 * n * n * 36];

	// Front side of the square
	for (int i = 0; i != n; ++i)
	{
		for (int j = 0; j != n; ++j)
		{
			for (int k = 0; k != 36; k += 6)
			{
				square[36 * n * i + 36 * j + k] = base_sq[k] + j * size / n;
				square[36 * n * i + 36 * j + k + 1] = base_sq[k + 1] + i * size / n;
				square[36 * n * i + 36 * j + k + 2] = size / 2;
				square[36 * n * i + 36 * j + k + 3] = 0.0f;
				square[36 * n * i + 36 * j + k + 4] = 0.0f;
				square[36 * n * i + 36 * j + k + 5] = 1.0f;
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
		side_offset = i * 36 * n * n;

		coef_22 = cos(i * M_PI * 0.5f);
		coef_32 = sin(i * M_PI * 0.5f);
		coef_23 = -sin(i * M_PI * 0.5f);
		coef_33 = cos(i * M_PI * 0.5f);

		for (int j = 0; j < 36 * n * n; j += 6)
		{
			square[side_offset + j] = square[j];
			square[side_offset + j + 1] = square[j + 1] * coef_22 + square[j + 2] * coef_23;
			square[side_offset + j + 2] = square[j + 1] * coef_32 + square[j + 2] * coef_33;
			square[side_offset + j + 3] = 0.0f;
			square[side_offset + j + 4] = coef_23;
			square[side_offset + j + 5] = coef_33;
		}
	}

	// Rotation by y axis - > 90 degress
	coef_11 = cos(M_PI * 0.5f);
	coef_31 = -sin(M_PI * 0.5f);
	coef_13 = sin(M_PI * 0.5f);
	coef_33 = cos(M_PI * 0.5f);

	side_offset = 4 * 36 * n * n;

	for (int j = 0; j < 36 * n * n; j += 6)
	{
		square[side_offset + j] = square[j] * coef_11 + square[j + 2] * coef_13;
		square[side_offset + j + 1] = square[j + 1];
		square[side_offset + j + 2] = square[j] * coef_31 + square[j + 2] * coef_33;
		square[side_offset + j + 3] = coef_13;
		square[side_offset + j + 4] = 0.0f;
		square[side_offset + j + 5] = coef_33;
	}

	// Rotation by y axis - > 270 degress
	coef_11 = cos(3.0f * M_PI * 0.5f);
	coef_31 = -sin(3.0 * M_PI * 0.5f);
	coef_13 = sin(3.0f * M_PI * 0.5f);
	coef_33 = cos(3.0f * M_PI * 0.5f);

	side_offset = 5 * 36 * n * n;

	for (int j = 0; j < 36 * n * n; j += 6)
	{
		square[side_offset + j] = square[j] * coef_11 + square[j + 2] * coef_13;
		square[side_offset + j + 1] = square[j + 1];
		square[side_offset + j + 2] = square[j] * coef_31 + square[j + 2] * coef_33;
		square[side_offset + j + 3] = coef_13;
		square[side_offset + j + 4] = 0.0f;
		square[side_offset + j + 5] = coef_33;
	}

	// Cube to sphere mapping -> source: http://mathproofs.blogspot.cz/2005/07/mapping-cube-to-sphere.html
	float tmp_x = 0.0f;
	float tmp_y = 0.0f;
	float tmp_z = 0.0f;

	for (int i = 0; i < 6 * n * n * 36; i += 6)
	{
		tmp_x = pow(1.0 - 0.5 * square[i + 1] * square[i + 1] - 0.5 * square[i + 2] * square[i + 2] + 0.33333 * square[i + 1] * square[i + 1] * square[i + 2] * square[i + 2], 0.5);
		tmp_y = pow(1.0 - 0.5 * square[i + 2] * square[i + 2] - 0.5 * square[i] * square[i] + 0.33333 * square[i] * square[i] * square[i + 2] * square[i + 2], 0.5);
		tmp_z = pow(1.0 - 0.5 * square[i + 1] * square[i + 1] - 0.5 * square[i] * square[i] + 0.33333 * square[i + 1] * square[i + 1] * square[i] * square[i], 0.5);

		square[i] *= tmp_x;
		square[i + 1] *= tmp_y;
		square[i + 2] *= tmp_z;

		// Adjustment of normals
		glm::mat3 tmp_mat = glm::mat3(
			tmp_x, 0.0f, 0.0f, 
			0.0f, tmp_y, 0.0f,
			0.0f, 0.0f, tmp_z
		);

		glm::vec3 normal = glm::normalize(glm::transpose(glm::inverse(tmp_mat)) * glm::vec3(square[i + 3], square[i + 4], square[i + 5]));

		square[i + 3] = normal.x;
		square[i + 4] = normal.y;
		square[i + 5] = normal.z;
	}

	return square;
}