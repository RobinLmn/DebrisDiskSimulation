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
	SDebrisDisk::SDebrisDisk(uint32_t ParticlesPerOrbit, std::string OrbitFile, float FixedRadiation, const SStar& Star)
		: ParticlesPerOrbit(ParticlesPerOrbit), OrbitFile(OrbitFile), FixedRadiation(FixedRadiation), Star(Star)
	{}

	void SDebrisDisk::Init()
	{
		ZoneScoped

		OrbitsFromFile(OrbitFile);

		for (int i = 0; i < Orbits.size(); i++)
		{
			std::vector<SParticle> OrbitParticles = *OrbitToParticle(Orbits[i]);
			Particles.insert(Particles.end(), OrbitParticles.begin(), OrbitParticles.end());
		}

		int Count = Particles.size();

		LOG_INFO("Particles Count: {0} ; Unconverging Anomalies: {1}", Count, UnconvergingAnomaly);
	}

	float SDebrisDisk::SolveEccentricAnomaly(float M /*Mean Anomaly*/, float e /*Orbit eccentricity*/ )
	{
		ZoneScoped

		float E = M;	// guess, E ~ M
		float F = E - e * glm::sin(E) - M;
		int j = 0, MaxIter = 100;
		while (glm::abs(F) > 0.0001f && j < MaxIter)
		{
			E = E - F / (1.f - e * glm::cos(E));
			F = E - e * glm::sin(E) - M;
			j++;
		}
		if (j >= MaxIter) UnconvergingAnomaly++;

		return E;
	}

	std::vector<SParticle>* SDebrisDisk::OrbitToParticle(SOrbit O)
	{
		ZoneScoped

		std::vector<SParticle>* ParticlesInOrbit = new std::vector<SParticle>();
		ParticlesInOrbit->reserve(ParticlesPerOrbit);

		for (uint32_t i = 0; i < ParticlesPerOrbit; i++)
		{
			// Random Mean Anomaly
			float M = glm::linearRand(-PI, PI);
			// Eccentric Anomaly
			float E = SolveEccentricAnomaly(M, O.e);

			float f = 0.5f * glm::sqrt( (1.f + O.e)/(1.f - O.e) ) * glm::tan(E * 0.5f);
			f = 2.f * glm::atan(f);
			f = f < 0.f ? 2.f * PI + f : f;

			float r = O.a * (1 - (O.e * O.e)) / (1 + O.e * glm::cos(f));

			float x = r * ( glm::cos(O.Omega) * glm::cos(O.omega + f) - glm::sin(O.Omega) * glm::sin(O.omega + f) * glm::cos(O.I) );
			float y = r * ( glm::sin(O.Omega) * glm::cos(O.omega + f) + glm::cos(O.Omega) * glm::sin(O.omega + f) * glm::cos(O.I) );
			float z = r * ( glm::sin(O.omega + f) * glm::sin(O.I) );
		
			SParticle DustParticle;
			DustParticle.Rad2 = x*x + y*y + z*z;
			DustParticle.Beta = O.Beta;
			DustParticle.Pos = glm::vec4(y, z, -x, 1.f);
			DustParticle.Temp = Star.Temp * glm::sqrt(Star.Radius / glm::sqrt(DustParticle.Rad2));
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
				
				SOrbit NewOrbit;
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
