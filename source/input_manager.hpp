#pragma once

#include <glm/glm.hpp>

namespace sim
{
	class input_manager
	{
	public:
		static bool is_key_pressed(int key_code);
		static bool is_mouse_button_pressed(int button);
		static glm::vec2 get_mouse_position();
	};
}