#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace app
{
	struct particle
	{
		glm::vec4 position;				// in AU
		alignas(16) float rad2;			// in AU
		float beta;						// Radiation
		float temp;						// in Kelvin
	};

	struct star
	{
		float radius;				// in AU
		float temp;					// in Kelvin
		float mass;					// in Solar Mass
	};

	struct orbit
	{
		float a;					// Semi Major Axis
		float e;					// Eccentricity
		float I;					// Inclinaison
		float Omega;				// Longitude of Ascending Node
		float omega;				// Argument of Periapse
		float Beta;					// Radiation
	};

	std::vector<particle> create_debris_disk(const std::vector<orbit>& orbits, int particles_per_orbit, const star& disk_star);
}