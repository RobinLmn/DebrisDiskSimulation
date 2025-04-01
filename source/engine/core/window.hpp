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

	private:
		GLFWwindow* native_window;
	};
}