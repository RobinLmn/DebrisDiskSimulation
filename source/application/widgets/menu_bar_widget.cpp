#include "menu_bar_widget.hpp"

#include "utils/file_utility.hpp"

#include <string>
#include <imgui.h>

namespace app
{
    menu_bar_widget::menu_bar_widget(menu_bar_widget_delegates&& delegates)
        : delegates{ std::move(delegates) }
    {
    }

    void menu_bar_widget::draw()
    {
        if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
					delegates.on_new_scene_requested();

				if (ImGui::MenuItem("Open", "Ctrl+O"))
				{
					std::string filename = utils::open_file_dialog("content/simulations/", "Simulation Files\0*.sim\0");
					if (!filename.empty())
						delegates.on_open_scene_requested(filename.c_str());
				}

				ImGui::Separator();

				if (ImGui::MenuItem("Export"))
					delegates.on_export_requested();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
    }
}
