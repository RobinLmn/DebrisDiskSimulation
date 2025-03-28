#include "input_manager.hpp"

#include <glfw/glfw3.h>

namespace sim
{
	bool input_manager::is_key_pressed(int key_code)
	{
		GLFWwindow* window = glfwGetCurrentContext();
		const int state = glfwGetKey(window, key_code);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool input_manager::is_mouse_button_pressed(int button)
	{
		GLFWwindow* window = glfwGetCurrentContext();
		const int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	glm::vec2 input_manager::get_mouse_position()
	{
		double x_pos, y_pos;
		GLFWwindow* window = glfwGetCurrentContext();
		glfwGetCursorPos(window, &x_pos, &y_pos);

		return glm::vec2{ x_pos, y_pos };
	}
}
