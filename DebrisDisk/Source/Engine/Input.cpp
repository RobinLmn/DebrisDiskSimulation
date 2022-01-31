#include "Input.h"

#include "Engine.h"
#include "Window.h"
#include <GLFW/glfw3.h>

namespace DebrisDisk
{
	bool FInput::IsKeyPressed(int KeyCode)
	{
		GLFWwindow* Window = static_cast<GLFWwindow*>(FEngine::GetEngine().GetWindow().GetNativeWindow());
		int State = glfwGetKey(Window, KeyCode);
		return State == GLFW_PRESS || State == GLFW_REPEAT;
	}

	bool FInput::IsMouseButtonPressed(int MouseButton)
	{
		GLFWwindow* Window = static_cast<GLFWwindow*>(FEngine::GetEngine().GetWindow().GetNativeWindow());
		int State = glfwGetMouseButton(Window, MouseButton);
		return State == GLFW_PRESS;
	}

	glm::vec2 FInput::GetMousePos()
	{
		GLFWwindow* Window = static_cast<GLFWwindow*>(FEngine::GetEngine().GetWindow().GetNativeWindow());
		double XPos,YPos;
		glfwGetCursorPos(Window, &XPos, &YPos);
		return glm::vec2(XPos, YPos);
	}
}