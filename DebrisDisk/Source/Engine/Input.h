#pragma once

#include "glm/glm.hpp"

namespace DebrisDisk
{
	class FInput
	{
	public:
		static bool IsKeyPressed(int KeyCode);
		static bool IsMouseButtonPressed(int Button);
		static glm::vec2 GetMousePos();
	};
}