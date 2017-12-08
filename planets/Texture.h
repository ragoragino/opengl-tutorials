#pragma once
#include "Perlin.h"
#include "sphere.h"

void create_terrain(float * source, unsigned int size_source, unsigned int offset = 6, float edge = 0.6)
{
	for (unsigned int i = 0; i != size_source; i += offset)
	{
		float noise = perlin_noise(source[i], source[i + 1], source[i + 2]);
		noise = noise * (1 - edge) + edge; // map to edge - 1.0 values

		source[i] *= noise;
		source[i + 1] *= noise;
		source[i + 2] *= noise;
	}

}