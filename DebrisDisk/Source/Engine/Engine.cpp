#include "Engine.h"
#include "Tracy/Tracy.hpp"

namespace DebrisDisk
{
	FEngine::FEngine()
	{
		ZoneScoped

		int Width = 1080;
		int Height = 720;
		glm::vec3 InitialCamPos = glm::vec3(0.f, 0.f, 0.f);
		float Fov = 90.f;
		float NearPlane = 0.f;
		float FarPlane = 100.f;

		float AspectRatio = static_cast<float>(Width) / static_cast<float>(Height);
		RCamera* Camera = new RCamera(InitialCamPos, Fov, AspectRatio, NearPlane, FarPlane);

		Window = new FWindow(Width, Height, false);
		Log = new FLog();
		Scene = new RScene(Camera);
		CameraController = new SCameraController(Camera);
	}

	void FEngine::Run()
	{
		ZoneScoped

		Log->Init();
		Window->Init();
		Scene->Init();

		LOG_INFO("Engine Initialized");

		std::chrono::high_resolution_clock Clock;
		using seconds = std::chrono::duration<float, std::ratio<1>>;
		auto LastTime = Clock.now();

		while (bRunning)
		{
			FrameMark

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