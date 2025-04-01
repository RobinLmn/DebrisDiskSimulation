#include "framebuffer.hpp"

#include "engine/core/log.hpp"

#include <glad/glad.h>

namespace engine
{
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
}
