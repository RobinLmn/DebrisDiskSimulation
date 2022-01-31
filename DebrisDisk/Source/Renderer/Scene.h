#pragma once

#include "Shader.h"

namespace DebrisDisk
{
	class RScene
	{
	public:
		void Init();
		void Render();
		void Terminate();

	private:
		unsigned int VBO, VAO;
		RShader* Shader;
	};
}