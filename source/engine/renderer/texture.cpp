#include "texture.hpp"

#include "engine/core/log.hpp"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

namespace engine
{
	texture_1d::texture_1d(const char* filename, const unsigned int unit)
		: unit{ unit }
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_1D, id);

		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		int width, height, channel_count;
		unsigned char* texture_data = stbi_load(filename, &width, &height, &channel_count, 0);

		ASSERT(texture_data != nullptr, return, "Failed to load texture %s", filename);

		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, width, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
		stbi_image_free(texture_data);

		glBindTexture(GL_TEXTURE_1D, 0);
	}

	texture_1d::~texture_1d()
	{
		glDeleteTextures(1, &id);
	}

	void texture_1d::bind() const
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_1D, id);
	}

	void texture_1d::unbind() const
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_1D, 0);
	}

	unsigned int texture_1d::get_unit() const
	{
		return unit;
	}
}