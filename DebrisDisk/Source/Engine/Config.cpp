#include "Config.h"

#include <string>
#include "Log.h"
#include <fstream>

namespace DebrisDisk
{
	FConfig::FConfig()
	{
		std::string Line;
		std::ifstream File("Content/.config");
		std::vector<std::string> ConfigParams;

		if (!File.is_open())
		{
			LOG_ERROR("Unable to open config file.");
			return;
		}

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

		ParticlesPerOrbit = std::stoi(ConfigParams[0]);
		Width = std::stoi(ConfigParams[1]);
		Height = std::stoi(ConfigParams[2]);
		Fov = std::stof(ConfigParams[3]);
		NearPlane = std::stof(ConfigParams[4]);
		FarPlane = std::stof(ConfigParams[5]);
		FixedRadiation = std::stof(ConfigParams[6]);
		Star.Radius = std::stof(ConfigParams[7]);
		Star.Mass = std::stof(ConfigParams[8]);
		Star.Temp = std::stof(ConfigParams[9]);
		OrbitFile = ConfigParams[10];

		File.close();

		return;
	}

}