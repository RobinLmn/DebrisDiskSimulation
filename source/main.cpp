#include <engine.hpp>
#include <input_manager.hpp>
#include <log.hpp>
#include <camera.hpp>
#include <scene.hpp>
#include <new_scene_window.hpp>

#include <file_utility.hpp>

#include <vector>
#include <chrono>

#include <glm/glm.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glfw/glfw3.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

void setup_dark_theme()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;

	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
	colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

int main()
{
	sim::logger::initialize();

	sim::window window{ 1920, 1080, "Debris Disk Simulation" };
	sim::renderer renderer;
	sim::shader shader{ "content/shaders/vertex.glsl", "content/shaders/fragment.glsl" };
	sim::camera camera{ 45.f, 1.f, 0.f, 100.f };
	sim::scene_hierarchy scene_hierarchy{};

	const auto on_scene_created = [&scene_hierarchy, &renderer](sim::scene&& scene)
	{
		renderer.load_particles(scene.get_particles().size(), sizeof(sim::particle), scene.get_particles().data());
		scene_hierarchy.add(std::move(scene));
	};

	sim::new_scene_window new_scene_window{ on_scene_created };

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
	ImGui_ImplOpenGL3_Init("#version 450");
	setup_dark_theme();

	camera.set_settings(50.f, 0.2f);
	camera.teleport(500.f, 0.f, 90.f);

	sim::texture_1d scattering_texture{ "content/textures/scattering.png", 0 };
	sim::texture_1d thermal_texture{ "content/textures/thermal.png", 1 };

	thermal_texture.bind();
	scattering_texture.bind();

	ImVec2 last_viewport_size{ 0, 0 };

	const auto clock = std::chrono::high_resolution_clock{};
	auto last_time = clock.now();

	bool thermal_radiation = false;
	float intensity = 1.4f;
	float offset = 0.0f;
	float dust_contribution = 0.1f;
	bool show_info = false;

	while (window.is_open())
	{
		using seconds = std::chrono::duration<float, std::ratio<1>>;
		const auto delta_time = std::chrono::duration_cast<seconds>(clock.now() - last_time).count();
		last_time = clock.now();

		camera.update(delta_time);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiDockNodeFlags docking_flags = ImGuiDockNodeFlags_None;
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		ImGuiViewport* main_viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(main_viewport->Pos);
		ImGui::SetNextWindowSize(main_viewport->Size);
		ImGui::SetNextWindowViewport(main_viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.14f, 0.14f, 0.14f, 1.00f));
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		if (docking_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		{
			window_flags |= ImGuiWindowFlags_NoBackground;
		}

		static bool dockspace_open = true;
		static bool take_screenshot = false;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("dockspace", &dockspace_open, window_flags);
		{
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
			ImGui::PopStyleVar(2);

			ImGui::DockSpace(ImGui::GetID("dockspace"), ImVec2(0.0f, 0.0f), docking_flags);

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New", "Ctrl+N"))
					{
						new_scene_window.show();
					}

					if (ImGui::MenuItem("Open", "Ctrl+O"))
					{
						std::string filename = sim::open_file_dialog("", "");
						sim::scene scene{ filename.c_str() };
						renderer.load_particles(scene.get_particles().size(), sizeof(sim::particle), scene.get_particles().data());

						scene_hierarchy.add(std::move(scene));
					}

					ImGui::Separator();

					if (ImGui::MenuItem("Export"))
					{
						take_screenshot = true;
					}

					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			ImGui::Begin("Viewport");
			{
				ImVec2 viewport_size = ImGui::GetContentRegionAvail();

				if (viewport_size.x != last_viewport_size.x || viewport_size.y != last_viewport_size.y)
				{
					renderer.create_framebuffer((int)viewport_size.x, (int)viewport_size.y);
					last_viewport_size = viewport_size;

					float aspect_ratio = viewport_size.x / viewport_size.y;
					camera.set_aspect_ratio(aspect_ratio);
				}

				renderer.bind_framebuffer((int)viewport_size.x, (int)viewport_size.y);

				renderer.clear();

				shader.use();
				shader.set_uniform("view_projection", camera.get_view_projection());
				shader.set_uniform("camera_position", camera.get_position());
				shader.set_uniform("thermal_radiation", thermal_radiation);
				shader.set_uniform("intensity", intensity);
				shader.set_uniform("offset", offset);
				shader.set_uniform("dust_contribution", dust_contribution);
				shader.set_uniform("colormap", thermal_radiation ? thermal_texture : scattering_texture);

				renderer.render();

				if (take_screenshot)
				{
					int width = (int)viewport_size.x;
					int height = (int)viewport_size.y;

					std::vector<unsigned char> buffer = renderer.read_pixels(width, height);

					std::vector<unsigned char> flipped_buffer(width * height * 3);
					for (int y = 0; y < height; y++)
					{
						memcpy(flipped_buffer.data() + y * width * 3, buffer.data() + (height - 1 - y) * width * 3, width * 3);
					}

					std::string filename = sim::new_file_dialog("debris_disk.png", "", "Png Files\0*.png\0");
					stbi_write_png(filename.c_str(), width, height, 3, flipped_buffer.data(), width * 3);

					take_screenshot = false;
				}

				renderer.unbind_framebuffer();

				ImGui::Image((void*)(intptr_t)renderer.get_render_texture(), viewport_size);

				ImGui::SetCursorPos(ImVec2(viewport_size.x - 40, 35));
				if (ImGui::Button("Info", ImVec2(40, 20)))
				{
					show_info = !show_info;
				}

				if (show_info)
				{
					ImGui::SetCursorPos(ImVec2(viewport_size.x - 120, 60));
					ImGui::BeginGroup();
					ImGui::Text("Particles: %.0e", static_cast<float>(renderer.get_particle_count()));
					ImGui::Text("FPS: %.1f", 1.0f / delta_time);
					ImGui::EndGroup();
				}
			}
			ImGui::End();

			ImGui::Begin("Properties");
			{
				if (ImGui::Button("Reset"))
				{
					intensity = 1.4f;
					offset = 0.0f;
					dust_contribution = 0.1f;

					camera.teleport(500.0f, 0.0f, 0.0f);
					camera.set_settings(50.0f, 0.2f);
				}

				if (ImGui::CollapsingHeader("Debris Disk", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::Checkbox("Thermal Radiation", &thermal_radiation);
					ImGui::DragFloat("Intensity", &intensity, 0.01f, 0.0f, 10.0f, "%.2f");
					ImGui::DragFloat("Offset", &offset, 0.01f, -1.0f, 1.0f, "%.2f");
					ImGui::DragFloat("Dust Contribution", &dust_contribution, 0.001f, 0.0f, 1.0f, "%.3f");
				}

				if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::Text("Position");
					float distance = camera.get_distance();
					float altitude = camera.get_altitude();
					float azimuth = camera.get_azimuth();

					bool position_changed = false;
					position_changed |= ImGui::DragFloat("Distance", &distance, 1.f, 10.0f, 1000.0f, "%.1f");
					position_changed |= ImGui::DragFloat("Altitude", &altitude, 0.1f, -90.0f, 90.0f, "%.1f");
					position_changed |= ImGui::DragFloat("Azimuth", &azimuth, 0.1f, 0.f, 180.0f, "%.1f");

					if (position_changed)
					{
						camera.teleport(distance, azimuth, altitude);
					}

					ImGui::Separator();

					ImGui::Text("Settings");
					static float sensitivity = 0.2f;
					static float speed = 50.0f;

					bool settings_changed = false;
					settings_changed |= ImGui::DragFloat("Sensitivity", &sensitivity, 0.01f, 0.05f, 1.0f, "%.1f");
					settings_changed |= ImGui::DragFloat("Speed", &speed, 1.f, 1.f, 100.0f, "%.2f");

					if (settings_changed)
					{
						camera.set_settings(speed, sensitivity);
					}
				}
			}
			ImGui::End();

			ImGui::Begin("Scenes");
			{
				if (ImGui::BeginTable("ScenesTable", 1, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
				{
					const auto& scenes = scene_hierarchy.get_all_scenes();
					for (size_t i = 0; i < scenes.size(); i++)
					{
						ImGui::TableNextRow();
						ImGui::TableNextColumn();

						ImGui::Selectable(scenes[i].get_filename(), false, ImGuiSelectableFlags_SpanAllColumns);

						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
						{
							renderer.load_particles(scenes[i].get_particles().size(), sizeof(sim::particle), scenes[i].get_particles().data());
						}
					}

					ImGui::EndTable();
				}
			}
			ImGui::End();
		}
		ImGui::End();

		new_scene_window.render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}