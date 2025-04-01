#include "window.hpp"

#include "engine/core/log.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace
{
	void on_window_resize(GLFWwindow* window, const int width, const int height)
	{
		// @todo: should that be done in the renderer?
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
}