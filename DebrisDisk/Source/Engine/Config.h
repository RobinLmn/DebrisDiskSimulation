#pragma once

#include <string>
#include "Systems/CelestialBodies.h"

namespace DebrisDisk
{
	class FConfig
	{
	public:
		FConfig();

	public:
		int ParticlesPerOrbit;
		int Width;
		int Height;
		float Fov;
		float NearPlane;
		float FarPlane;
		float FixedRadiation;
		SStar Star;
		std::string OrbitFile;
	};
}