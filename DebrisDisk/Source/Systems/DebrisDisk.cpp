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

		std::vector<std::thread> Threads;
		const size_t OrbitSize = Orbits.size();
		const size_t Workers = std::thread::hardware_concurrency();
		const size_t OrbitsPerThread = OrbitSize / Workers;

		for (int i = 0; i < ParticlesPerOrbit * OrbitSize; i++)
		{
			Particles.emplace_back(SParticle());
		}

		auto ConvertOrbitsToParticles = [this]( const int StartIndex, const int EndIndex)
		{
			for (size_t i = StartIndex; i < EndIndex; i++)
			{
				OrbitToParticle(Orbits[i], i * ParticlesPerOrbit);
			}
		};

		for (size_t i = 0; i < Workers - 1; ++i)
		{
			Threads.emplace_back(ConvertOrbitsToParticles, i * OrbitsPerThread, (i + 1) * OrbitsPerThread);
		}
		Threads.emplace_back(ConvertOrbitsToParticles, (Workers-1) * OrbitsPerThread, OrbitSize);

		for (std::thread& thread : Threads)
		{
			thread.join();
		}

		LOG_INFO("Particles Count: {0}", Particles.size());
	}

	float SDebrisDisk::SolveEccentricAnomaly(const float M /*Mean Anomaly*/, const float e /*Orbit eccentricity*/ ) const
	{
		ZoneScoped

		float E = M;	// guess, E ~ M
		float F = E - e * glm::sin(E) - M;
		int j = 0;
		const int MaxIter = 100;
		while (glm::abs(F) > 0.0001f && j < MaxIter)
		{
			E = E - F / (1.f - e * glm::cos(E));
			F = E - e * glm::sin(E) - M;
			j++;
		}

		return E;
	}

	void SDebrisDisk::OrbitToParticle(const SOrbit& O, const int index)
	{
		ZoneScoped

		for (uint32_t i = 0; i < ParticlesPerOrbit; i++)
		{
			// Random Mean Anomaly
			const float M = glm::linearRand(-PI, PI);
			// Eccentric Anomaly
			const float E = SolveEccentricAnomaly(M, O.e);

			float f = 0.5f * glm::sqrt( (1.f + O.e)/(1.f - O.e) ) * glm::tan(E * 0.5f);
			f = 2.f * glm::atan(f);
			f = f < 0.f ? 2.f * PI + f : f;

			const float r = O.a * (1 - (O.e * O.e)) / (1 + O.e * glm::cos(f));

			const float x = r * ( glm::cos(O.Omega) * glm::cos(O.omega + f) - glm::sin(O.Omega) * glm::sin(O.omega + f) * glm::cos(O.I) );
			const float y = r * ( glm::sin(O.Omega) * glm::cos(O.omega + f) + glm::cos(O.Omega) * glm::sin(O.omega + f) * glm::cos(O.I) );
			const float z = r * ( glm::sin(O.omega + f) * glm::sin(O.I) );
		
			SParticle DustParticle;
			DustParticle.Rad2 = x*x + y*y + z*z;
			DustParticle.Beta = O.Beta;
			DustParticle.Pos = glm::vec4(y, z, -x, 1.f);
			DustParticle.Temp = Star.Temp * glm::sqrt(Star.Radius / glm::sqrt(DustParticle.Rad2));
			Particles[i + index] = DustParticle;
		}
	}

	void SDebrisDisk::OrbitsFromFile(const std::string Filename)
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
					const char c = Line[i];

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
