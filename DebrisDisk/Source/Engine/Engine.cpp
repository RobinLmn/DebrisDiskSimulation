#include "Engine.h"

namespace DebrisDisk
{
	FEngine::FEngine()
	{
		Window = new FWindow(1080, 720, false);
		Log = new FLog();
		Scene = new RScene();
	}

	void FEngine::Run()
	{
		Log->Init();
		Window->Init();
		Scene->Init();

		LOG_INFO("Engine Initialized");

		while (bRunning)
		{
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