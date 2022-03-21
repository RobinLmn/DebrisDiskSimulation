#include "Engine.h"
#include "Tracy/Tracy.hpp"

namespace DebrisDisk
{
	FEngine::FEngine()
	{
		ZoneScoped

		int Width = 1080;
		int Height = 1080;
		float Fov = 45.f;
		float NearPlane = 0.f;
		float FarPlane = 100.f;
		uint32_t ParticlesPerOrbit = 1000;
		float FixedRadiation = 0.35f;
		//std::string OrbitFile = "Content/dustorbit/single_inner_planet_single_collision_inclined_beta0.35_dustorbit.txt"; // moth		
		std::string OrbitFile = "Content/dustorbit/single_inner_planet_e0.0_Ifree0_efree0_betadistrb1.5_bmin0.001_bmax1.0_dustorbit.txt"; // ring
		//std::string OrbitFile = "Content/dustorbit/single_inner_planet_e0.10_Ifree0_efree0_beta0.4_dustorbit.txt"; // 10,000 orbits fixed beta
		

		float AspectRatio = static_cast<float>(Width) / static_cast<float>(Height);
		RCamera* Camera = new RCamera(Fov, AspectRatio, NearPlane, FarPlane);

		Window = new FWindow(Width, Height, false);
		Log = new FLog();
		DebrisDisk = new SDebrisDisk(ParticlesPerOrbit, OrbitFile, FixedRadiation);
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
			DebrisDisk->Update(DeltaTime);
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
