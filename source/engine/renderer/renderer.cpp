#include "renderer.hpp"

#include "engine/core/log.hpp"

#include <glad/glad.h>

namespace engine
{
	renderer::renderer()
		: particle_count{ 0 }
		, particle_buffer{ 0 }
	{
		glGenVertexArrays(1, &vao);

		glEnable(GL_PROGRAM_POINT_SIZE);
		glPointSize(1);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDisable(GL_DEPTH_TEST);
	}

	renderer::~renderer()
	{
		glDeleteVertexArrays(1, &vao);

		if (particle_buffer != 0)
			glDeleteBuffers(1, &particle_buffer);
	}

	void renderer::load_particles(const size_t particle_count, const size_t particle_size, const void* particles)
	{
		ASSERT(particles != nullptr, return, "particles were nullptr");

		if (particle_buffer != 0)
			glDeleteBuffers(1, &particle_buffer);

		this->particle_count = particle_count;

		glGenBuffers(1, &particle_buffer);

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, particle_buffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, particle_count * particle_size, particles, GL_STATIC_DRAW);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	framebuffer renderer::create_framebuffer(const int width, const int height)
	{
		framebuffer new_framebuffer;

		new_framebuffer.width = width;
		new_framebuffer.height = height;

		glGenFramebuffers(1, &new_framebuffer.id);
		glBindFramebuffer(GL_FRAMEBUFFER, new_framebuffer.id);

		glGenTextures(1, &new_framebuffer.render_texture);
		glBindTexture(GL_TEXTURE_2D, new_framebuffer.render_texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, new_framebuffer.render_texture, 0);

		return new_framebuffer;
	}

	std::vector<unsigned char> renderer::read_pixels(const int width, const int height) const
	{
		std::vector<unsigned char> pixels(width * height * 4);
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
		return pixels;
	}

	void renderer::clear()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void renderer::render()
	{
		if (particle_count == 0)
			return;

		glBindVertexArray(vao);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particle_buffer);

		glDrawArraysInstanced(GL_POINTS, 0, 1, static_cast<GLsizei>(particle_count));
	}
}