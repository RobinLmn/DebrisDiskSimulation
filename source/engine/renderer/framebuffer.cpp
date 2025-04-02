#include "framebuffer.hpp"

#include "engine/core/log.hpp"

#include <glad/glad.h>

namespace engine
{
	framebuffer::framebuffer(const int width, const int height)
		: width{ width }
		, height{ height }
		, id{ 0 }
		, render_texture{ 0 }
	{
		recreate();
	}

	framebuffer::~framebuffer()
	{
		unbind();
		
		glDeleteFramebuffers(1, &id);
		glDeleteTextures(1, &id);
	}

    void framebuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, id);
		glViewport(0, 0, width, height);
	}

	void framebuffer::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	unsigned int framebuffer::get_render_texture() const
	{
		return render_texture;
	}

	void framebuffer::resize(const int new_width, const int new_height)
	{
		width = new_width;
		height = new_height;

		recreate();
	}

	void framebuffer::recreate()
	{
		if (id)
		{
			glDeleteFramebuffers(1, &id);
		}

		glGenFramebuffers(1, &id);
		glBindFramebuffer(GL_FRAMEBUFFER, id);

		glGenTextures(1, &render_texture);
		glBindTexture(GL_TEXTURE_2D, render_texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, render_texture, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
