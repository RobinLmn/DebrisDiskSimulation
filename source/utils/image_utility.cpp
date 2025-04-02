#include "utils/image_utility.hpp"

#include "engine/core/log.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

namespace utils
{
	std::vector<unsigned char> load_image(const char* filename, int& width, int& height, int& channels)
	{
		unsigned char* texture_data = stbi_load(filename, &width, &height, &channels, 0);
		ASSERT(texture_data != nullptr, return {}, "Failed to load texture %s", filename);

        std::vector<unsigned char> data(texture_data, texture_data + width * height * channels);
		stbi_image_free(texture_data);

		return data;
	}

	void save_image(const char* filename, int width, int height, int channels, const unsigned char* data)
	{
		stbi_write_png(filename, width, height, channels, data, width * channels);
	}
}