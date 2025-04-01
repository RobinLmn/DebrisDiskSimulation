#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <cstdint>

#include "application/simulation/simulation.hpp"

namespace utils
{
	bool save_particles_to_file(const std::vector<app::particle>& particles, const std::string& filename);
	std::vector<app::particle> load_particles_from_file(const std::string& filename);

	std::vector<app::orbit> load_orbits_from_file(const char* filename, const float fixed_radiation);

	std::string open_file_dialog(const char* initial_directory, const char* files_filter);
	std::string new_file_dialog(const char* initial_filename, const char* initial_directory, const char* files_filter);
}
