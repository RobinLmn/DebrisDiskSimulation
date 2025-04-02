#include "scene_view_widget.hpp"

#include "application/simulation/scene.hpp"

#include <imgui.h>

namespace app
{
	scene_view_widget::scene_view_widget(scene_view_widget_delegates&& delegates)
		: delegates{ std::move(delegates) }
	{
	}

    void scene_view_widget::draw()
    {
        ImGui::Begin("Scenes");
		{
			if (ImGui::BeginTable("ScenesTable", 1, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
			{
				const std::vector<scene>& scenes = delegates.get_all_scenes();
				for (size_t i = 0; i < scenes.size(); i++)
				{
					ImGui::TableNextRow();
					ImGui::TableNextColumn();

					ImGui::Selectable(scenes[i].get_filename(), false, ImGuiSelectableFlags_SpanAllColumns);

					if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
					{
						delegates.on_scene_selected(scenes[i]);
					}
				}

				ImGui::EndTable();
			}
		}
		ImGui::End();
    }
}
