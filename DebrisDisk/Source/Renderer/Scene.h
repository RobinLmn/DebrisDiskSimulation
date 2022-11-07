#pragma once

#include "Shader.h"
#include "Camera.h"
#include "Systems/DebrisDisk.h"
#include <string>

namespace DebrisDisk
{
	class RScene
	{
	public:
		RScene(RCamera* Camera, SDebrisDisk* Disk);

		void Init();
		void Render();
		void Terminate();

		static void Screenshot(std::string Filename);

		unsigned int GetRenderTexture() const { return RenderTexture; }

	private:
		void LoadTexture(std::string Filename);

	private:
		unsigned int VBO = 0, VAO = 0, ParticleBuffer = 0, FBO = 0;
		unsigned int ScatteringTexture = 0, ThermalTexture = 0, RenderTexture = 0;

		SDebrisDisk* Disk;
		RShader* Shader = nullptr;
		RCamera* Camera;
	};
}