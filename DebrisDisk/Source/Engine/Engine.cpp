#include "Engine.h"

namespace DebrisDisk
{
	FEngine::FEngine()
	{
		float Width = 1080.f;
		float Height = 720.f;

		RCamera* Camera = new RCamera(90.f, Width / Height, 10.f, -1.f);

		Window = new FWindow(Width, Height, false);
		Log = new FLog();
		Scene = new RScene(Camera);
		CameraController = new SCameraController(Camera);
	}

	void FEngine::Run()
	{
		Log->Init();
		Window->Init();
		Scene->Init();

		LOG_INFO("Engine Initialized");

		std::chrono::high_resolution_clock Clock;
		using seconds = std::chrono::duration<float, std::ratio<1>>;
		auto LastTime = Clock.now();

		while (bRunning)
		{
			const float deltaTime = std::chrono::duration_cast<seconds>(Clock.now() - LastTime).count();
			LastTime = Clock.now();

			CameraController->Update(deltaTime);
			Scene->Render();
			Window->Update();
		}

		Scene->Terminate();
		Window->Terminate();
	}

	FEngine::~FEngine()
	{
		delete Window;
		delete Log;
		delete Scene;
	}
}