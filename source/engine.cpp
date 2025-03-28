#include "engine.hpp"

#include "log.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"

#include <fstream>
#include <sstream>

namespace
{
	void on_window_resize(GLFWwindow* window, const int width, const int height)
	{
		glViewport(0, 0, width, height);
	}

#ifdef DEBUG
	void check_shader_compile_errors(unsigned int shaderID, std::string type)
	{
		int success;
		char infoLog[1024];

		if (type != "PROGRAM")
		{
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);

			ASSERT(success, return, "SHADER_COMPILATION_ERROR of type: {0}\n{1}", type, infoLog)
		}
		else
		{
			glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
			glGetProgramInfoLog(shaderID, 1024, NULL, infoLog);

			ASSERT(success, return, "PROGRAM_LINKING_ERROR of type: {0}\n{1}", type, infoLog)
		}
	}
#endif
}

namespace sim
{
	window::window(int width, int height, const char* title)
		: native_window{ nullptr }
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		native_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		glfwMakeContextCurrent(native_window);
		glfwSetFramebufferSizeCallback(native_window, on_window_resize);

		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}

	void window::update()
	{
		glfwPollEvents();
		glfwSwapBuffers(native_window);
	}

	bool window::is_open() const
	{
		return !glfwWindowShouldClose(native_window);
	}

	window::~window()
	{
		glfwDestroyWindow(native_window);
		glfwTerminate();
	}

	shader::shader(const char* vertex_path, const char* fragment_path)
	{
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		vShaderFile.open(vertex_path);
		fShaderFile.open(fragment_path);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		std::string vertexCode = vShaderStream.str();
		std::string fragmentCode = fShaderStream.str();

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

#ifdef DEBUG
		check_shader_compile_errors(vertex, "VERTEX");
#endif

		unsigned int fragment;
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

#ifdef DEBUG
		check_shader_compile_errors(fragment, "FRAGMENT");
#endif

		id = glCreateProgram();
		glAttachShader(id, vertex);
		glAttachShader(id, fragment);
		glLinkProgram(id);

#ifdef DEBUG
		check_shader_compile_errors(id, "PROGRAM");
#endif

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	shader::~shader()
	{
		glDeleteProgram(id);
	}

	void shader::use() const
	{
		glUseProgram(id);
	}

	template<>
	void shader::set_uniform<bool>(const char* name, const bool& value) const
	{
		glUniform1i(glGetUniformLocation(id, name), (int)value);
	}

	template<>
	void shader::set_uniform<int>(const char* name, const int& value) const
	{
		glUniform1i(glGetUniformLocation(id, name), value);
	}

	template<>
	void shader::set_uniform<float>(const char* name, const float& value) const
	{
		glUniform1f(glGetUniformLocation(id, name), value);
	}

	template<>
	void shader::set_uniform<glm::vec2>(const char* name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(id, name), 1, &value[0]);
	}

	template<>
	void shader::set_uniform<glm::vec3>(const char* name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(id, name), 1, &value[0]);
	}

	template<>
	void shader::set_uniform<glm::vec4>(const char* name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(id, name), 1, &value[0]);
	}

	template<>
	void shader::set_uniform<glm::mat4>(const char* name, const glm::mat4& value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, &value[0][0]);
	}

	template<>
	void shader::set_uniform<texture_1d>(const char* name, const texture_1d& value) const
	{
		glUniform1i(glGetUniformLocation(id, name), value.get_unit());
	}

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

	renderer::renderer()
		: particle_count{ 0 }
		, particle_buffer{ 0 }
	{
		glGenVertexArrays(1, &vao);

		glEnable(GL_PROGRAM_POINT_SIZE);
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

	void renderer::load_particles(const size_t in_particle_count, const size_t particle_size, const void* particles)
	{
		ASSERT(particles != nullptr, return, "particles were nullptr");

		if (particle_buffer != 0)
			glDeleteBuffers(1, &particle_buffer);

		particle_count = in_particle_count;

		glGenBuffers(1, &particle_buffer);

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, particle_buffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, particle_count * particle_size, particles, GL_STATIC_DRAW);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	void renderer::clear()
	{
		glClearColor(0.f, 0.f, 0.f, 1.0f);
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