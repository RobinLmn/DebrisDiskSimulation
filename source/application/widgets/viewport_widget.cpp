#include "viewport_widget.hpp"

#include <imgui.h>

namespace app
{
	viewport_widget::viewport_widget(viewport_widget_delegates&& delegates)	
		: delegates{ std::move(delegates) }
	{
	}

    void viewport_widget::draw()
    {
        ImGui::Begin("Viewport");
		{
			ImVec2 viewport_size = ImGui::GetContentRegionAvail();

			unsigned int render_texture = delegates.request_draw(static_cast<int>(viewport_size.x), static_cast<int>(viewport_size.y));
			ImGui::Image((void*)(intptr_t)render_texture, viewport_size);

			ImGui::SetCursorPos(ImVec2(viewport_size.x - 40, 35));
			if (ImGui::Button("Info", ImVec2(40, 20)))
			{
				show_info = !show_info;
			}

			if (show_info)
			{
				ImGui::SetCursorPos(ImVec2(viewport_size.x - 120, 60));
				ImGui::BeginGroup();
				{
					info_widget_properties properties = delegates.get_info_widget_properties();
					ImGui::Text("Particles: %.0e", static_cast<float>(properties.particle_count));
					ImGui::Text("FPS: %.1f", properties.fps);
				}
				ImGui::EndGroup();
			}
		}
		ImGui::End();
    }
}
