#pragma once

#include <GLFW/glfw3.h>

namespace DebrisDisk
{
	class FWindow
	{
	public:
		FWindow(int width, int height, int vsync);

		void Init();
		void Update();
		void Terminate();

		inline GLFWwindow* GetNativeWindow() const { return NativeWindow; }

	public:
		int Width;
		int Height;
		bool bVSync;

	private:
		GLFWwindow* NativeWindow;
	};
}
