#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <cstdint>

#include "simulation.hpp"

namespace sim
{
    bool save_particles_to_file(const std::vector<particle>& particles, const star& star, const std::string& filename);
    std::pair<std::vector<particle>, star> load_particles_from_file(const std::string& filename);

    std::vector<orbit> load_orbits_from_file(const char* filename, float fixed_radiation);
}
