#include "simulation.hpp"

#include "log.hpp"

#include <glm/gtc/random.hpp>
#include <glm/gtc/constants.hpp>

#include <fstream>
#include <sstream>
#include <string>
#include <thread>

#define PI glm::pi<float>()

namespace
{
	float solve_eccentric_anomaly(const float M /*Mean Anomaly*/, const float e /*Orbit eccentricity*/)
	{
		float E = M;	// guess, E ~ M
		float F = E - e * glm::sin(E) - M;
		int j = 0;
		const int max_iter = 100;
		while (glm::abs(F) > 0.0001f && j < max_iter)
		{
			E = E - F / (1.f - e * glm::cos(E));
			F = E - e * glm::sin(E) - M;
			j++;
		}

		return E;
	}

	void add_orbit_to_disk_at_index(std::vector<sim::particle>& debris_disk, const sim::orbit& orbit, const size_t index, const int particles_per_orbit, const sim::star& star)
	{
		for (int i = 0; i < particles_per_orbit; i++)
		{
			// Random Mean Anomaly
			const float M = glm::linearRand(-PI, PI);
			// Eccentric Anomaly
			const float E = solve_eccentric_anomaly(M * 0.5f, orbit.e);

			float f = glm::sqrt((1.f + orbit.e) / (1.f - orbit.e)) * glm::tan(E);
			f = 2.f * glm::atan(f);
			f = f < 0.f ? 2.f * PI + f : f;

			const float r = orbit.a * (1 - (orbit.e * orbit.e)) / (1 + orbit.e * glm::cos(f));

			const float x = r * (glm::cos(orbit.Omega) * glm::cos(orbit.omega + f) - glm::sin(orbit.Omega) * glm::sin(orbit.omega + f) * glm::cos(orbit.I));
			const float y = r * (glm::sin(orbit.Omega) * glm::cos(orbit.omega + f) + glm::cos(orbit.Omega) * glm::sin(orbit.omega + f) * glm::cos(orbit.I));
			const float z = r * (glm::sin(orbit.omega + f) * glm::sin(orbit.I));

			sim::particle particle;
			particle.rad2 = r * r;
			particle.beta = orbit.Beta;
			particle.position = glm::vec4(y, z, -x, 1.f);
			particle.temp = star.temp * glm::sqrt(star.radius / glm::sqrt(particle.rad2));
			debris_disk[index + i] = particle;
		}
	}
}

namespace sim
{
	std::vector<particle> create_debris_disk(const std::vector<orbit>& orbits, const int particles_per_orbit, const star& disk_star)
	{
		const size_t orbit_count = orbits.size();
		const size_t particle_count = particles_per_orbit * orbit_count;

		std::vector<particle> debris_disk{ particle_count };

		const auto add_orbits_to_disk_range = [&orbits, &debris_disk, &particles_per_orbit, &disk_star](const size_t start_index, const size_t end_index)
		{
			for (size_t i = start_index; i < end_index; ++i)
			{
				add_orbit_to_disk_at_index(debris_disk, orbits[i], i * particles_per_orbit, particles_per_orbit, disk_star);
			}
		};

		std::vector<std::thread> threads;
		constexpr size_t workers = 8;
		const size_t orbits_per_thread = orbit_count / workers;

		for (size_t i = 0; i < workers - 1; ++i)
		{
			threads.emplace_back(add_orbits_to_disk_range, i * orbits_per_thread, (i + 1) * orbits_per_thread);
		}
		threads.emplace_back(add_orbits_to_disk_range, (workers - 1) * orbits_per_thread, orbit_count);

		for (std::thread& thread : threads)
		{
			thread.join();
		}

		return debris_disk;
	}

	std::vector<orbit> load_orbits_from_file(const char* filename, const float fixed_radiation)
	{
		std::string line;
		std::ifstream file(filename);

		ASSERT(file.is_open(), return {}, "Unable to open orbit file.");

		std::vector<orbit> orbits;

		while (std::getline(file, line))
		{
			std::vector<float> Params;
			std::string currentParam;

			for (int i = 0; i < line.length(); i++)
			{
				const char c = line[i];

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

			orbit new_orbit;
			new_orbit.a = Params[0];
			new_orbit.e = Params[1];
			new_orbit.I = Params[2];
			new_orbit.Omega = Params[3];
			new_orbit.omega = Params[4];
			new_orbit.Beta = Params.size() > 5 ? Params[5] : fixed_radiation;

			orbits.push_back(new_orbit);
		}

		file.close();

		return orbits;
	}
}