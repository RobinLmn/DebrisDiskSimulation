#include "window.hpp"

#include "engine/core/log.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace
{
	void on_window_resize(GLFWwindow* window, const int width, const int height)
	{
		glViewport(0, 0, width, height);
	}
}

namespace engine
{
	window::window(const int width, const int height, const char* title)
		: native_window{ nullptr }
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
#ifdef PLATFORM_MACOS
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		native_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		glfwMakeContextCurrent(native_window);
		glfwSetFramebufferSizeCallback(native_window, on_window_resize);

		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}

	window::~window()
	{
		glfwDestroyWindow(native_window);
		glfwTerminate();
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

	void window::set_icon(unsigned char* pixels, const int width, const int height)
	{
		ASSERT(pixels != nullptr, return, "pixels were nullptr");

		GLFWimage icon;
		icon.width = width;
		icon.height = height;
		icon.pixels = pixels;

		glfwSetWindowIcon(native_window, 1, &icon);
	}
}