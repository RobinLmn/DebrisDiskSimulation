#pragma once

namespace engine
{
    class shader
	{
	public:
		shader(const char* vertex_path, const char* fragment_path);
		~shader();

	public:
		void use() const;

		template<typename T>
		void set_uniform(const char* name, const T& value) const;

	private:
		unsigned int id;
	};
}