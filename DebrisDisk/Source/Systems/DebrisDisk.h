#pragma once

#include <vector>
#include "Systems/Particle.h"

namespace DebrisDisk
{
	class SDebrisDisk
	{
	public:
		void Init();

	public:
		size_t Count;
		std::vector<Particle> Particles;
	};
}