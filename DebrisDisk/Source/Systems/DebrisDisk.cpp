#include "DebrisDisk.h"
#include "Engine/Log.h"

#include <glm/gtc/random.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <fstream>
#include <sstream>

#include <Tracy/Tracy.hpp>

#define PI glm::pi<float>()

namespace DebrisDisk
{
	SDebrisDisk::SDebrisDisk(uint32_t ParticlesPerOrbit, std::string OrbitFile, float FixedRadiation)
		: ParticlesPerOrbit(ParticlesPerOrbit), OrbitFile(OrbitFile), FixedRadiation(FixedRadiation)
	{}

	void SDebrisDisk::Init()
	{
		ZoneScoped

		OrbitsFromFile(OrbitFile);

		for (int i = 0; i < Orbits.size(); i++)
		{
			std::vector<Particle> OrbitParticles = *OrbitToParticle(Orbits[i]);
			Particles.insert(Particles.end(), OrbitParticles.begin(), OrbitParticles.end());
		}

		Count = static_cast<uint32_t>(Orbits.size()) * ParticlesPerOrbit;
	}

	std::vector<Particle>* SDebrisDisk::OrbitToParticle(Orbit O)
	{
		ZoneScoped

		std::vector<Particle>* ParticlesInOrbit = new std::vector<Particle>();
		ParticlesInOrbit->reserve(ParticlesPerOrbit);

		for (uint32_t i = 0; i < ParticlesPerOrbit; i++)
		{
			// Random Mean Anomaly
			float M = glm::linearRand(-PI, PI);				

			// Newton approximation for Eccentric Anomaly
			float E = M;	// guess, E ~ M
			float F = E - O.e * glm::sin(E) - M;
			int j = 0;
			while (glm::abs(F) > 0.0001f && j < 100) 
			{
				E = E - F / (1.f - O.e * glm::cos(E));
				F = E - O.e * glm::sin(E) - M;
				j++;
			}

			float f = 0.5f * glm::sqrt( (1.f + O.e)/(1.f - O.e) ) * glm::tan(E * 0.5f);
			f = 2.f * glm::atan(f);
			f = f < 0.f ? 2.f * PI + f : f;

			float r = O.a * (1 - (O.e * O.e)) / (1 + O.e * glm::cos(f));

			float x = r * ( glm::cos(O.Omega) * glm::cos(O.omega + f) - glm::sin(O.Omega) * glm::sin(O.omega + f) * glm::cos(O.I) );
			float y = r * ( glm::sin(O.Omega) * glm::cos(O.omega + f) + glm::cos(O.Omega) * glm::sin(O.omega + f) * glm::cos(O.I) );
			float z = r * ( glm::sin(O.omega + f) * glm::sin(O.I) );
		
			Particle DustParticle;
			DustParticle.Rad2 = x*x + y*y + z*z;
			DustParticle.Beta = O.Beta;
			DustParticle.Pos = glm::vec4(x, z, y, 1.f);
			ParticlesInOrbit->push_back(DustParticle);
		}

		return ParticlesInOrbit;
	}

	void SDebrisDisk::Update(float DeltaTime)
	{
	}

	void SDebrisDisk::OrbitsFromFile(std::string Filename)
	{
		ZoneScoped
		std::string Line;
		std::ifstream File(Filename);

		if (File.is_open())
		{

			while (std::getline(File, Line))
			{
				std::vector<float> Params;
				std::string currentParam;

				for (int i = 0; i < Line.length(); i++)
				{
					char c = Line[i];

					if (c == ' ')
					{
						Params.push_back(std::stof(currentParam));
						currentParam = "";
					}
					else
					{
						currentParam.append(1, c);
					}
				}

				Params.push_back(std::stof(currentParam));
				
				Orbit NewOrbit;
				NewOrbit.a = Params[0];
				NewOrbit.e = Params[1];
				NewOrbit.I = Params[2];
				NewOrbit.Omega = Params[3];
				NewOrbit.omega = Params[4];
				NewOrbit.Beta = Params.size() > 5 ? Params[5] : FixedRadiation;

				Orbits.push_back(NewOrbit);
			}

			File.close();
		}
		else LOG_ERROR("Unable to open orbit file.");

		return;
	}
}