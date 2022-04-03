#pragma once

#include "Renderer/Camera.h"
#include <glm/glm.hpp>

namespace DebrisDisk
{
	class RCameraController
	{
	public:
		RCameraController(RCamera* Camera);
		void Update(float DeltaTime);

	public:
		RCamera* Camera;

	private:
		glm::vec2 MousePosition;
	};
}
