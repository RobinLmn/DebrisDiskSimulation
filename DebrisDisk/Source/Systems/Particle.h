#pragma once
#include <glm/glm.hpp>

struct Particle
{
	glm::vec4 Pos;
	alignas(16) float Rad2;			
	float Beta;		// Radiation
};