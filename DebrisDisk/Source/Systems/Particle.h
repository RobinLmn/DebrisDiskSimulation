#pragma once
#include <glm/glm.hpp>

namespace DebrisDisk
{
	struct SParticle
	{
		glm::vec4 Pos;				// in AU
		alignas(16) float Rad2;		// in AU
		float Beta;					// Radiation
		float Temp;					// in Kelvin
	};

	struct SStar
	{
		float Radius;				// in AU
		float Temp;					// in Kelvin
		float Mass;					// in Solar Mass
	};

	struct SOrbit
	{
		float a;					// Semi Major Axis
		float e;					// Eccentricity
		float I;					// Inclinaison
		float Omega;				// Longitude of Ascending Node
		float omega;				// Argument of Periapse
		float Beta;					// Radiation
	};
}