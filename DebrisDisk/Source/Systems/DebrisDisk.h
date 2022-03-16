#pragma once

#include <vector>
#include <string>
#include "Systems/Particle.h"
#include "Renderer/Camera.h"

namespace DebrisDisk
{
	struct Orbit
	{
		float a;		// Semi Major Axis
		float e;		// Eccentricity
		float I;		// Inclinaison
		float Omega;	// Longitude of Ascending Node
		float omega;	// Argument of Periapse
		float Beta;		// Radiation
	};

	class SDebrisDisk
	{
	public:
		SDebrisDisk(uint32_t ParticlesPerOrbit, std::string OrbitFile, float FixedRadiation);
		void Init();
		void Update(float DeltaTime);
		float SolveEccentricAnomaly(float M /*Mean Anomaly*/, float e /*Orbit eccentricity*/);

		void OrbitsFromFile(std::string Filename);
		std::vector<Particle>* OrbitToParticle(Orbit O);

	public:
		uint32_t Count = 0;
		uint32_t ParticlesPerOrbit;
		uint32_t UnconvergingAnomaly = 0;

		float FixedRadiation;
		float MaxBeta = FLT_MAX;
		float MaxRad2 = FLT_MAX;
		float StarRad = 0.00465f;	// in AU
		float StarTemp = 5000.f;	// in K

		std::string OrbitFile;

		std::vector<Particle> Particles;
		std::vector<Orbit> Orbits;
	};
}
