#include "Engine.h"
#include "Tracy/Tracy.hpp"
#include "Config.h"

#include <fstream>
#include <sstream>
#include <string>

namespace DebrisDisk
{
	FEngine::FEngine()
	{
		ZoneScoped

		FConfig Config{};

		const float AspectRatio = static_cast<float>(Config.Width) / static_cast<float>(Config.Height);
		RCamera* Camera = new RCamera(Config.Fov, AspectRatio, Config.NearPlane, Config.FarPlane);

		Window = new FWindow(Config.Width, Config.Height, false);
		Log = new FLog();
		DebrisDisk = new SDebrisDisk(Config.ParticlesPerOrbit, Config.OrbitFile, Config.FixedRadiation, Config.Star);
		Scene = new RScene(Camera, DebrisDisk);
		CameraController = new RCameraController(Camera);
		Editor = new FEditor(Camera);
	}

	void FEngine::Run()
	{
		ZoneScoped

		Log->Init();
		Window->Init();
		DebrisDisk->Init();
		Scene->Init();
		Editor->Init();

		LOG_INFO("Engine Initialized");

		std::chrono::high_resolution_clock Clock;
		using seconds = std::chrono::duration<float, std::ratio<1>>;
		auto LastTime = Clock.now();

		while (bRunning)
		{
			FrameMark

			const float DeltaTime = std::chrono::duration_cast<seconds>(Clock.now() - LastTime).count();
			LastTime = Clock.now();

			Editor->NewFrame();

			CameraController->Update(DeltaTime);
			Editor->Update(DeltaTime);

			Scene->Render();
			Editor->Render();
			Window->Update();
		}

		Scene->Terminate();
		Window->Terminate();
		Editor->Terminate();
	}

	FEngine::~FEngine()
	{
		delete Window;
		delete Log;
		delete Scene;
	}
}
