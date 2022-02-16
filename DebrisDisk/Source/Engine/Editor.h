#pragma once

#include "Renderer/Camera.h"

namespace DebrisDisk
{
	class FEditor
	{
	public:
		FEditor(RCamera* Camera);

		void Init();

		void NewFrame();
		void Update(float DeltaTime);
		void Render();

		void Terminate();

	private:
		bool bScreenshot = false;
		RCamera* Camera;
		char Filename[128] = "Debris Disk";
	};
}
