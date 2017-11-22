#pragma once
#define _USE_MATH_DEFINES 
#include "math.h"

float * spire(float size, unsigned int n, int n_triangles)
{
	const float spire_height = pow(pow(size, 2.0) / 2.0, 0.5); // height of the spire
	const float x_add = size / (2 * n); // step in the x direction for new point
	const float y_add = spire_height / n; // step in the y direction for new point
	const float z_add = size / (2 * n); // step in the z direction for new point

	unsigned int index = 0;
	const int side = n_triangles * 3 * 3; // number of points for all vertices
	float * spire = new float[side]; // spire object
	unsigned int counter = 2 * n - 1; // counter of triangles in a given row
	bool ident = false; // true means that next point should be in the 
						// upper row, while false means that it should be in the lower row

	// first, second, third and last point in the row
	float first_point[3] = { -size / 2.0, 0.0, size / 2.0 };
	float second_point[3] = { first_point[0] + x_add,
		first_point[1] + y_add, first_point[2] - z_add };
	float third_point[3];
	float border_point[3] = { size / 2.0, 0.0, size / 2.0 };

	for (int i = 0; i != n; ++i)
	{
		for(int j = 0; j != counter; ++j)
		{
			if (ident)
			{
				third_point[0] = second_point[0] + x_add;
				third_point[1] = second_point[1] + y_add;
				third_point[2] = second_point[2] - z_add;

			}
			else
			{
				third_point[0] = second_point[0] + x_add;
				third_point[1] = second_point[1] - y_add;
				third_point[2] = second_point[2] + z_add;
			}

			ident = !ident;

			// Append new triange to the spire array
			spire[index] = first_point[0];
			spire[index + 1] = first_point[1];
			spire[index + 2] = first_point[2];

			spire[index + 3] = second_point[0];
			spire[index + 4] = second_point[1];
			spire[index + 5] = second_point[2];

			spire[index + 6] = third_point[0];
			spire[index + 7] = third_point[1];
			spire[index + 8] = third_point[2];

			index += 9;

			// Update current position
			first_point[0] = second_point[0];
			first_point[1] = second_point[1];
			first_point[2] = second_point[2];

			second_point[0] = third_point[0];
			second_point[1] = third_point[1];
			second_point[2] = third_point[2];

		}

		// Jump to new row
		border_point[0] = first_point[0];
		border_point[1] = first_point[1];
		border_point[2] = first_point[2];

		first_point[0] = border_point[0] - (size - (i + 1)  * size / n);
		first_point[1] = border_point[1];
		first_point[2] = border_point[2];

		second_point[0] = first_point[0] + x_add;
		second_point[1] = first_point[1] + y_add;
		second_point[2] = first_point[2] - z_add;

		ident = !ident;
		
		counter -= 2;
	}

	return spire;
}