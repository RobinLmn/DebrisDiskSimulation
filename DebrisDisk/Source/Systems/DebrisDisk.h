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

	private:
		float SolveEccentricAnomaly(const float M /*Mean Anomaly*/, const float e /*Orbit eccentricity*/) const;

		void OrbitsFromFile(const std::string Filename);
		void OrbitToParticle(const SOrbit& O, const int index);

	private:
		const uint32_t ParticlesPerOrbit;
		const float FixedRadiation;

		SStar Star;

		const std::string OrbitFile;

		std::vector<SOrbit> Orbits;

	public:
		std::vector<SParticle> Particles;
	};
}
