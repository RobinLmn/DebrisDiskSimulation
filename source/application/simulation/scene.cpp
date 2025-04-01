#include "scene.hpp"

#include "utils/file_utility.hpp"

namespace app
{
	scene::scene(const star& disk_star, const char* orbits_file, const float fixed_radiation, const int particles_per_orbit, const char* filepath)
		: filename{ filepath }
	{
		const std::vector<orbit>& orbits = utils::load_orbits_from_file(orbits_file, fixed_radiation);
		particles = create_debris_disk(orbits, particles_per_orbit, disk_star);

		utils::save_particles_to_file(particles, filepath);
	}

	scene::scene(const char* filepath)
		: filename{ filepath }
	{
		particles = utils::load_particles_from_file(filename);
	}

	const std::vector<particle>& scene::get_particles() const
	{
		return particles;
	}

	const char* scene::get_filename() const
	{
		return filename.c_str();
	}

	void scene_hierarchy::add(scene&& scene)
	{
		scenes.emplace_back(scene);
	}

	const std::vector<scene>& scene_hierarchy::get_all_scenes() const
	{
		return scenes;
	}
}
