#pragma once

#include "Shader.h"
#include "Camera.h"
#include "Systems/DebrisDisk.h"

namespace DebrisDisk
{
	class RScene
	{
	public:
		RScene(RCamera* Camera, SDebrisDisk* Disk);

		void Init();
		void Render();
		void Terminate();

	private:
		unsigned int VBO = 0, VAO = 0, ParticleBuffer = 0, Texture = 0;

		SDebrisDisk* Disk;
		RShader* Shader = nullptr;
		RCamera* Camera;
	};
}