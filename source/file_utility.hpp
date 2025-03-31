#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <cstdint>

#include "simulation.hpp"

namespace sim
{
	bool save_particles_to_file(const std::vector<particle>& particles, const std::string& filename);
	std::vector<particle> load_particles_from_file(const std::string& filename);

	std::vector<orbit> load_orbits_from_file(const char* filename, const float fixed_radiation);

	std::string open_file_dialog(const char* initial_directory, const char* files_filter);
	std::string new_file_dialog(const char* initial_filename, const char* initial_directory, const char* files_filter);
}
