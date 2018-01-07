#pragma once
#include "sphere.h"
#include "Noise.h"
#include "Header.h"
#include "Solar.h"

const int N_METEORS = 1000; // Must be also defined in meteor fragment shaders !!!

float * meteor_f(int n, int offset = 6, float in_ampl = 0.5f, float in_freq = 0.5f, 
	float ampl_mult = 0.35f, float freq_mult = 0.4f, int octave = 5, float magnitude = 0.5f)
{
	float * meteor = sphere(n);
	
	float frac_noise;
	float tmp_x = 0.0f;
	float tmp_y = 0.0f;
	float tmp_z = 0.0f;

	float freq;
	float ampl;
	
	for (int i = 0; i < 6 * n * n * 18; i += 3)
	{
		freq = in_freq;
		ampl = in_ampl;
		frac_noise = 0.0f;

		tmp_x = meteor[i] * freq;
		tmp_y = meteor[i + 1] * freq;
		tmp_z = meteor[i + 2] * freq;

		for (int j = 0; j != octave; ++j)
		{
			frac_noise += noise(tmp_x, tmp_y, tmp_z) * ampl;
			ampl *= ampl_mult;
			freq *= freq_mult;
			tmp_x *= freq;
			tmp_y *= freq;
			tmp_z *= freq;
		}

		meteor[i] *= frac_noise + magnitude;
		meteor[i + 1] *= frac_noise + magnitude;
		meteor[i + 2] *= frac_noise + magnitude;
	}
	
	return meteor;
}

glm::mat4 * InitializeMeteorRing(float x_offset = 1.0f, float y_offset = 0.05f, float z_offset = 1.0f)
{
	glm::mat4 * meteor_rings = new glm::mat4[N_METEORS];
	float x, z, random;

	for (int i = 0; i < N_METEORS; i += 1)
	{
		random = (float)rand() / (float)RAND_MAX;
		x = meteor_distance * (float)sin(2.0f * M_PI * random);
		z = meteor_distance * (float)cos(2.0f * M_PI * random);
		meteor_rings[i] = glm::translate(glm::mat4(), 
			glm::vec3(x + x_offset * (2.0f * (float)rand() / (float)RAND_MAX - 1.0f),
			y_offset * meteor_distance * (2.0f * (float)rand() / (float)RAND_MAX - 1.0f),
			z + z_offset * (2.0f * (float)rand() / (float)RAND_MAX - 1.0f)
			));
		meteor_rings[i] = glm::rotate(meteor_rings[i], glm::radians((float)(rand() % 360)), glm::vec3(x, (float)rand() / (float)RAND_MAX, z));
		meteor_rings[i] = glm::scale(meteor_rings[i], meteor_scale * (0.5f + (float)rand() / (float)RAND_MAX));
	}

	return meteor_rings;
}

// Sinusoid movement
float * InitializeMeteorRingFlucation(int fluctation_length = 5)
{
	float * meteor_ring_fluctuation = new float[N_METEORS];

	for (int i = 0; i < N_METEORS; ++i)
	{
		// The values need to be continuous!
		meteor_ring_fluctuation[i] = (float)sin(2.0f * M_PI * i / ((float)N_METEORS / (float)fluctation_length ) );
	}

	return meteor_ring_fluctuation;
}


