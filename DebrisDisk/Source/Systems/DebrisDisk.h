#pragma once

#include <vector>
#include <string>
#include "Systems/Particle.h"
#include "Renderer/Camera.h"

namespace DebrisDisk
{
	class SDebrisDisk
	{
	public:
		SDebrisDisk(uint32_t ParticlesPerOrbit, std::string OrbitFile, float FixedRadiation, const SStar& Star);
		void Init();
		void Update(float DeltaTime);
		float SolveEccentricAnomaly(float M /*Mean Anomaly*/, float e /*Orbit eccentricity*/);

		void OrbitsFromFile(std::string Filename);
		std::vector<SParticle>* OrbitToParticle(SOrbit O);

	public:
		uint32_t Count = 0;
		uint32_t ParticlesPerOrbit;
		uint32_t UnconvergingAnomaly = 0;

		float FixedRadiation;

		SStar Star;

		std::string OrbitFile;

		std::vector<SParticle> Particles;
		std::vector<SOrbit> Orbits;
	};
}
