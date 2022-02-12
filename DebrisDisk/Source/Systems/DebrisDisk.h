#pragma once

#include <vector>
#include <string>
#include "Systems/Particle.h"

namespace DebrisDisk
{
	struct Orbit
	{
		float a;			// SemiMajorAxis;	
		float e;			// Eccentricity;		 
		float I;			// Inclinaison;		
		float Omega;		// AscendNodeLong;	
		float omega;		// PeriapseArg;	
		float Beta;			// Radiation;	
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