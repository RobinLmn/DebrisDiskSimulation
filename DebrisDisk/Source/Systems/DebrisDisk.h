#pragma once

#include <vector>
#include <string>
#include "Systems/Particle.h"

namespace DebrisDisk
{
	struct Orbit
	{
		float SemiMajorAxis;	// a
		float Eccentricity;		// e
		float Inclinaison;		// I
		float AscendNodeLong;	// Omega
		float PeriapseArg;		// omega
		float Radiation;		// Beta
	};

	class SDebrisDisk
	{
	public:
		void Init();

		void OrbitsFromFile(std::string Filename);
		std::vector<Particle>* OrbitToParticle(Orbit O);

		void MakeFlatDisk();

	public:
		uint32_t Count;
		uint32_t ParticlesPerOrbit;

		float FixedRadiation;

		std::vector<Particle> Particles;
		std::vector<Orbit> Orbits;
	};
}