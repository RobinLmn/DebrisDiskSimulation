#include "Engine.h"

namespace DebrisDisk
{
	FEngine::FEngine()
	{
		Window = new FWindow(1080, 720, false);
		Log = new FLog();
	}

	void FEngine::Run()
	{
		Log->Init();
		Window->Init();

		LOG_INFO("Engine Initialized");

		while (bRunning)
		{
			Window->Update();
		}

		Window->Terminate();
	}

	FEngine::~FEngine()
	{
		delete Window;
		delete Log;
	}
}