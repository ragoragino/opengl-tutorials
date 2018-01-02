#pragma once
#include "Header.h"
#include "Freeimage.h"

class Snapshot
{
public:
	Snapshot(uint32_t in_width, uint32_t in_height, char * in_dir = "visuals\\snapshot_", size_t in_dir_size = sizeof("visuals\\snapshot_"),
		char * in_format = ".png", size_t in_format_size = sizeof(".png"), uint32_t in_max_snapshot_count = 3) :
		counter{ 0 },
		width{ in_width },
		height{ in_height },
		dir_size{ in_dir_size },
		format_size{ in_format_size },
		max_snapshot_count{ in_max_snapshot_count }
	{
		pixels = (BYTE*)malloc(3 * width * height);
		number_buffer = (char*)malloc(max_snapshot_count + 1);
		format = (char*)malloc(format_size);
		memcpy(format, in_format, format_size);
		output_name = (char*)malloc(dir_size + format_size + max_snapshot_count - 1); // max_snapshot_count means one byte for null termination and rest of the bytes for number
		memcpy(output_name, in_dir, dir_size);
	};

	~Snapshot()
	{
		free(pixels);
		free(number_buffer);
		free(format);
		free(output_name);
	};

	void Snapshot::take_snapshot();

	uint32_t counter, width, height, max_snapshot_count, dir_size, format_size;
	BYTE * pixels;
	char * format, * output_name, * number_buffer;
};

void Snapshot::take_snapshot()
{
	// Write the screenshot to the pixels variable
	glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, pixels);

	//  Obtain number of digits in the counter for the purpose of writing the output name
	uint32_t digits = 1;
	uint32_t denominator = 10;
	while(true)
	{
		if (counter / denominator < 1)
		{
			break;
		}
		else
		{
			denominator *= 10;
			++digits;
		}
	}

	if (digits > max_snapshot_count)
	{
		printf("Buffer of snapshost names is full. Increase the in_max_snapshsot_count variable in order to increase the number!");
	}

	// Write the image with the constructed output name
	_itoa(counter++, number_buffer, 10);
	FIBITMAP * image = FreeImage_ConvertFromRawBits(pixels, width, height, 3 * width, 24, 0x0000FF, 0x0000FF, 0x0000FF, false);
	memcpy(output_name + dir_size - 1, number_buffer, digits);
	memcpy(output_name + dir_size + digits - 1, format, format_size);
	remove(output_name);
	FreeImage_Save(FIF_PNG, image, output_name, PNG_DEFAULT);
	FreeImage_Unload(image);
}