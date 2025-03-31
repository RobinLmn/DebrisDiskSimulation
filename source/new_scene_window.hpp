#pragma once

#include "scene.hpp"

#include <functional>

namespace sim
{
	class new_scene_window
	{
	public:
		new_scene_window(const std::function<void(scene&&)>& on_scene_created_callback);

		void show();
		void render();

	private:
		bool is_visible = false;
		std::function<void(scene&&)> on_scene_created;

	private:
		char orbits_file[256] = "";
		char filepath[256] = "";
		float star_mass = 0.001f;
		float star_luminosity = 5000.f;
		float star_radius = 1.f;
		float fixed_radiation = 0.35f;
		int particles_per_orbit = 200;
	};
}