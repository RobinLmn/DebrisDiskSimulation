#pragma once

#include "Window.h"
#include "Log.h"
#include "Renderer/Scene.h"
#include "Renderer/CameraController.h"
#include "Systems/DebrisDisk.h"
#include "Editor.h"

namespace DebrisDisk
{
	struct FConfig
	{
		uint32_t ParticlesPerOrbit;
		int Width;
		int Height;
		float Fov;
		float NearPlane;
		float FarPlane;
		float FixedRadiation;
		float StarRadius;
		float StarMass;
		float StarTemp;
		std::string OrbitFile;
	};

	class FEngine
	{
	public:
		static FEngine& GetEngine() { static FEngine Engine; return Engine; }
		void ReadConfigFile();
		void Run();

		FEngine(FEngine& e) = delete;
		void operator=(const FEngine& e) = delete;
		~FEngine();

		inline const FWindow& GetWindow() const { return *Window; }
		static inline void Screenshot(std::string Filename) { RScene::Screenshot(Filename); }

	private:
		FEngine();

	private:
		bool bRunning = true;

		FConfig* Config = nullptr;
		FWindow* Window = nullptr;
		FLog* Log = nullptr;
		RScene* Scene = nullptr;
		RCameraController* CameraController = nullptr;
		SDebrisDisk* DebrisDisk = nullptr;
		FEditor* Editor = nullptr;
	};
}
