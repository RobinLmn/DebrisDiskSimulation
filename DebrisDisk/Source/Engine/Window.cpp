#include "Window.h"

#include "Log.h"
#include <glad/glad.h>

namespace DebrisDisk
{
	FWindow::FWindow(int width, int height, int vsync)
		: Width(width), Height(height), bVSync(vsync), NativeWindow(nullptr)
	{
	}

	void FWindow::Init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// MacOS: glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		NativeWindow = glfwCreateWindow(Width, Height, "Debris Disk Simulation", NULL, NULL);
		if (!NativeWindow)
		{
			LOG_ERROR("Failed to create GLFW window");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(NativeWindow);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("Failed to initialize GLAD");
			return;
		}

		glViewport(0, 0, Width, Height);
	}

	void FWindow::Update()
	{
		glfwSwapBuffers(NativeWindow);
		glfwPollEvents();
	}

	void FWindow::Terminate()
	{
		glfwTerminate();
	}
}