#pragma once

#include "Window.h"
#include "Log.h"
#include "Renderer/Scene.h"
#include "Systems/CameraController.h"

namespace DebrisDisk
{
	class FEngine
	{
	public:
		static FEngine& GetEngine() { static FEngine Engine; return Engine; }
		void Run();

		FEngine(FEngine& e) = delete;
		void operator=(const FEngine& e) = delete;
		~FEngine();

		inline const FWindow& GetWindow() const { return *Window; }

	private:
		FEngine();

	private:
		bool bRunning = true;

		FWindow* Window = nullptr;
		FLog* Log = nullptr;
		RScene* Scene = nullptr;
		SCameraController* CameraController = nullptr;
	};
}
