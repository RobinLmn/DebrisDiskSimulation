#pragma once

#include <vector>
#include <string>

struct GLFWwindow;

namespace engine
{
	class window
	{
	public:
		window(const int width, const int height, const char* title);
		~window();

	public:
		void update();
		bool is_open() const;

		void set_icon(unsigned char* pixels, const int width, const int height);

	private:
		GLFWwindow* native_window;
	};
}