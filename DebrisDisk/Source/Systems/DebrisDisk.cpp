#include "DebrisDisk.h"
#include <glm/gtc/random.hpp>

namespace DebrisDisk
{
	void SDebrisDisk::Init()
	{
		Count = 50000;

        Particles.reserve(Count);
		for (size_t i = 0; i < Count; i++)
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