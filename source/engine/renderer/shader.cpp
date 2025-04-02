#include "shader.hpp"

#include "engine/core/log.hpp"
#include "engine/renderer/texture.hpp"

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <fstream>
#include <sstream>

namespace
{
#ifdef DEBUG
	void check_shader_compile_errors(const unsigned int shaderID, const char* type)
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

namespace engine
{
    shader::shader(const char* vertex_path, const char* fragment_path)
	{
		std::ifstream v_shader_file;
		std::ifstream f_shader_file;

		v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		v_shader_file.open(vertex_path);
		f_shader_file.open(fragment_path);
		std::stringstream v_shader_stream, f_shader_stream;

		v_shader_stream << v_shader_file.rdbuf();
		f_shader_stream << f_shader_file.rdbuf();

		v_shader_file.close();
		f_shader_file.close();

		std::string vertex_code = v_shader_stream.str();
		std::string fragment_code = f_shader_stream.str();
		const char* v_shader_code = vertex_code.c_str();
		const char* f_shader_code = fragment_code.c_str();

		unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &v_shader_code, nullptr);
		glCompileShader(vertex);

#ifdef DEBUG
		check_shader_compile_errors(vertex, "VERTEX");
#endif

		unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &f_shader_code, nullptr);
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
}
