#include "Engine.h"
#include "Tracy/Tracy.hpp"

#include <fstream>
#include <sstream>
#include <string>

namespace DebrisDisk
{
	FEngine::FEngine()
	{
		ZoneScoped

		Config = new FConfig();
		ReadConfigFile();

		const float AspectRatio = static_cast<float>(Config->Width) / static_cast<float>(Config->Height);
		RCamera* Camera = new RCamera(Config->Fov, AspectRatio, Config->NearPlane, Config->FarPlane);

		SStar Star;
		Star.Radius = Config->StarRadius;
		Star.Mass = Config->StarMass;
		Star.Temp = Config->StarTemp;

		Window = new FWindow(Config->Width, Config->Height, false);
		Log = new FLog();
		DebrisDisk = new SDebrisDisk(Config->ParticlesPerOrbit, Config->OrbitFile, Config->FixedRadiation, Star);
		Scene = new RScene(Camera, DebrisDisk);
		CameraController = new RCameraController(Camera);
		Editor = new FEditor(Camera);

		delete Config;
	}

	void FEngine::ReadConfigFile()
	{
		std::string Line;
		std::ifstream File("Content/.config");
		std::vector<std::string> ConfigParams;

		if (File.is_open())
		{
			while (std::getline(File, Line))
			{
				if (Line.length() == 0 || Line[0] == '#')
					continue;

				std::string Param;

				int i;
				for (i = 0; i < Line.length(); i++)
					if (Line[i] == '=') break;

				for (i += 2; i < Line.length(); i++)
					Param.append(1, Line[i]);

				ConfigParams.push_back(Param);
			}

			Config->ParticlesPerOrbit	= std::stoi(ConfigParams[0]);
			Config->Width				= std::stoi(ConfigParams[1]);
			Config->Height				= std::stoi(ConfigParams[2]);
			Config->Fov					= std::stof(ConfigParams[3]);
			Config->NearPlane			= std::stof(ConfigParams[4]);
			Config->FarPlane			= std::stof(ConfigParams[5]);
			Config->FixedRadiation		= std::stof(ConfigParams[6]);
			Config->StarRadius			= std::stof(ConfigParams[7]);
			Config->StarMass			= std::stof(ConfigParams[8]);
			Config->StarTemp			= std::stof(ConfigParams[9]);
			Config->OrbitFile			= ConfigParams[10];

			File.close();
		}
		else LOG_ERROR("Unable to open config file.");

		return;
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
