#pragma once

namespace engine
{
	class texture_1d
	{
	public:
		texture_1d(const char* filename, const unsigned int unit);
		~texture_1d();

	public:
		void bind() const;
		void unbind() const;

		unsigned int get_unit() const;

	private:
		unsigned int id;
		unsigned int unit;
	};
}
