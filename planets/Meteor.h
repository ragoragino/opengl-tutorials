#pragma once
#include "sphere.h"
#include "Noise.h"

float * meteor_f(unsigned int n, unsigned int offset = 6, float in_ampl = 0.2f, float in_freq = 0.1f, 
	float ampl_mult = 0.35f, float freq_mult = 1.5f, unsigned int octave = 5)
{
	float * meteor = sphere(n);
	
	float frac_noise;
	float tmp_x = 0.0f;
	float tmp_y = 0.0f;
	float tmp_z = 0.0f;

	float freq;
	float ampl;
	
	for (int i = 0; i <= 6 * n * n * 36; i += 6)
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

		meteor[i] *= frac_noise + 0.5f;
		meteor[i + 1] *= frac_noise + 0.5f;
		meteor[i + 2] *= frac_noise + 0.5f;
	}
	
	return meteor;
}

