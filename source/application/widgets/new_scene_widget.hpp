#pragma once

#include "application/simulation/scene.hpp"
#include "engine/editor/widget.hpp"

#include <functional>

namespace app
{
	struct new_scene_widget_delegates
	{
		std::function<void(scene&&)> on_scene_created;
		std::function<bool()> should_popup;
	};	

	class new_scene_widget final : public engine::widget
	{
	public:
		explicit new_scene_widget(new_scene_widget_delegates&& delegates);

		virtual void draw() override;

	private:
		new_scene_widget_delegates delegates;

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