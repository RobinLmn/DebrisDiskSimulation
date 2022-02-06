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
	void SDebrisDisk::Init()
	{
		ZoneScoped

		ParticlesPerOrbit = 100;
		Particles.reserve(Count);

		OrbitsFromFile("Content/dustorbit/single_inner_planet_e0.7_Ifree0_efree0_betadistrb1.5_bmin0.001_bmax1.0_Isig0.15_orbcorr_morelaunch_dustorbit.txt");

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
			float Theta = glm::sqrt( (1.f + O.Eccentricity) / (1.f - O.Eccentricity) * glm::tan( glm::linearRand( -PI, PI ) ) );
			Theta = 2.f * glm::atan(Theta);
			Theta = Theta > 0 ? 2 * PI + Theta : Theta;

			float x = glm::cos(O.AscendNodeLong) * glm::cos(O.PeriapseArg + Theta) - glm::sin(O.AscendNodeLong) * glm::sin(O.PeriapseArg + Theta) * glm::cos(O.Inclinaison);
			float z = glm::sin(O.AscendNodeLong) * glm::cos(O.PeriapseArg + Theta) + glm::cos(O.AscendNodeLong) * glm::sin(O.PeriapseArg + Theta) * glm::cos(O.Inclinaison);
			float y = glm::sin(O.PeriapseArg + Theta) * glm::sin(O.Inclinaison);

			Particle DustParticle;
			DustParticle.Pos = glm::vec4(x, y, z, 1.f);
			ParticlesInOrbit->push_back(DustParticle);
		}

		return ParticlesInOrbit;
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
				NewOrbit.SemiMajorAxis = Params[0];
				NewOrbit.Eccentricity = Params[1];
				NewOrbit.Inclinaison = Params[2];
				NewOrbit.AscendNodeLong = Params[3];
				NewOrbit.PeriapseArg = Params[4];
				NewOrbit.Radiation = Params.size() > 5 ? Params[5] : FixedRadiation;

				Orbits.push_back(NewOrbit);
			}

			File.close();
		}
		else LOG_ERROR("Unable to open orbit file.");

		return;
	}

	void SDebrisDisk::MakeFlatDisk()
	{
		for (uint32_t i = 0; i < Count; i++)
		{
			glm::vec3 Pos;
			do {
				Pos = glm::ballRand(50.f);
				Pos.y *= 0.01f;
			} while (glm::length(Pos) < 10.0f);

			Particle DustParticle;
			DustParticle.Pos = glm::vec4(Pos, 1.0f);
			Particles.push_back(DustParticle);
		}
	}
}