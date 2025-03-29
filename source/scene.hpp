#pragma once

#include "simulation.hpp"

#include <string>

namespace sim
{
	class scene
	{
	public:
		scene(const star& disk_star, const char* orbits_file, const float fixed_radiation, const int particles_per_orbit, const char* filepath);
		scene(const char* filename);

	public:
		const std::vector<particle>& get_particles() const;
		const char* get_filename() const;

	private:
		std::vector<particle> particles;
		const std::string filename;
	};

	class scene_hierarchy
	{
	public:
		void add(scene&& scene);
		const std::vector<scene>& get_all_scenes() const;

	private:
		std::vector<scene> scenes;
	};
}