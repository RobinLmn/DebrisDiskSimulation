#include "properties_widget.hpp"

#include <imgui.h>

namespace app
{
	properties_widget::properties_widget(properties_widget_delegates&& delegates)
		: delegates{ std::move(delegates) }
	{
	}

    void properties_widget::draw()
    {
        ImGui::Begin("Properties");
		{
			if (ImGui::Button("Reset"))
				delegates.on_properties_reset_requested();

			debris_disk_widget_properties debris_disk = delegates.get_debris_disk_properties();
			camera_widget_properties camera = delegates.get_camera_properties();

			if (ImGui::CollapsingHeader("Debris Disk", ImGuiTreeNodeFlags_DefaultOpen))
			{
				bool debris_disk_changed = false;

				debris_disk_changed |= ImGui::Checkbox("Thermal Radiation", &debris_disk.thermal_radiation);
				debris_disk_changed |= ImGui::DragFloat("Intensity", &debris_disk.intensity, 0.01f, 0.0f, 10.0f, "%.2f");
				debris_disk_changed |= ImGui::DragFloat("Offset", &debris_disk.offset, 0.01f, -1.0f, 1.0f, "%.2f");
				debris_disk_changed |= ImGui::DragFloat("Dust Contribution", &debris_disk.dust_contribution, 0.001f, 0.0f, 1.0f, "%.3f");

				if (debris_disk_changed)
					delegates.on_debris_disk_properties_changed(debris_disk);
			}

			if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
			{
				bool camera_position_changed = false;
				bool camera_settings_changed = false;

				ImGui::Text("Position");
				camera_position_changed |= ImGui::DragFloat("Distance", &camera.distance, 1.f, 10.0f, 1000.0f, "%.1f");
				camera_position_changed |= ImGui::DragFloat("Altitude", &camera.altitude, 0.1f, -90.0f, 90.0f, "%.1f");
				camera_position_changed |= ImGui::DragFloat("Azimuth", &camera.azimuth, 0.1f, 0.f, 180.0f, "%.1f");

				ImGui::Separator();

				ImGui::Text("Settings");
				camera_settings_changed |= ImGui::DragFloat("Sensitivity", &camera.sensitivity, 0.01f, 0.05f, 1.0f, "%.1f");
				camera_settings_changed |= ImGui::DragFloat("Speed", &camera.speed, 1.f, 1.f, 100.0f, "%.2f");

				if (camera_position_changed)
					delegates.on_camera_position_changed(camera);

				if (camera_settings_changed)
					delegates.on_camera_settings_changed(camera);
			}
		}
		ImGui::End();
    }
}
