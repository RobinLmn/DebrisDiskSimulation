#include "new_scene_widget.hpp"

#include "utils/file_utility.hpp"

#include <imgui.h>

namespace app
{
	new_scene_widget::new_scene_widget(new_scene_widget_delegates&& delegates)
		: delegates{ std::move(delegates) }
	{
	}

	void new_scene_widget::draw()
	{
		if (delegates.should_popup())
		{
			ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_FirstUseEver);

			const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
			ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

			ImGui::OpenPopup("New Scene");
		}

		if (ImGui::BeginPopupModal("New Scene"))
		{
			const float content_height = ImGui::GetWindowHeight() - 60.0f;
			ImGui::BeginChild("Content", ImVec2(0, content_height));

			ImGui::Text("Star Properties");
			ImGui::InputFloat("Mass", &star_mass, 0.0001f, 0.0005f, "%.5f");
			ImGui::InputFloat("Luminosity", &star_luminosity, 100.0f, 1000.0f, "%.0f");
			ImGui::InputFloat("Radius", &star_radius, 0.1f, 0.5f, "%.1f");

			ImGui::Separator();

			ImGui::Text("Orbit Properties");

			if (ImGui::Button("Browse##1"))
			{
				const std::string filename = utils::open_file_dialog("content/dust_orbits/", "Text Files\0*.txt\0All Files\0*.*\0");
				if (!filename.empty())
					strcpy_s(orbits_file, filename.c_str());
			}

			ImGui::SameLine();
			ImGui::InputText("Orbits File", orbits_file, sizeof(orbits_file));

			ImGui::InputFloat("Fixed Radiation", &fixed_radiation, 0.01f, 0.1f, "%.2f");
			ImGui::InputInt("Particles per Orbit", &particles_per_orbit, 10, 100);

			ImGui::Separator();

			ImGui::Text("Save Location");
			if (ImGui::Button("Browse##2"))
			{
				const std::string filename = utils::new_file_dialog("debris_disk.sim", "content/simulations/", "Simulation Files\0*.sim\0All Files\0*.*\0");
				if (!filename.empty())
					strcpy_s(filepath, filename.c_str());
			}

			ImGui::SameLine();
			ImGui::InputText("Filepath", filepath, sizeof(filepath));

			ImGui::EndChild();

			ImGui::Separator();

			const float button_width = 120.0f;
			const float button_spacing = 20.0f;
			const float total_button_width = (button_width * 2) + button_spacing;
			ImGui::SetCursorPosX(ImGui::GetWindowWidth() - total_button_width - 20.0f);
			if (ImGui::Button("Create", ImVec2(button_width, 0)))
			{
				const star disk_star{ star_mass, star_luminosity, star_radius };
				scene new_scene{ disk_star, orbits_file, fixed_radiation, particles_per_orbit, filepath };

				delegates.on_scene_created(std::move(new_scene));
				ImGui::CloseCurrentPopup();
			}

			ImGui::SameLine();

			if (ImGui::Button("Cancel", ImVec2(button_width, 0)))
			{
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
}