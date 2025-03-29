#include <engine.hpp>
#include <input_manager.hpp>
#include <log.hpp>
#include <camera.hpp>
#include <simulation.hpp>

#include <vector>
#include <chrono>

#include <glm/glm.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

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
	sim::initialize_logger();

	sim::window window{ 1920, 1080, "Particle Renderer" };
	sim::renderer renderer;
	sim::shader shader{ "content/shaders/vertex.glsl", "content/shaders/fragment.glsl" };
	sim::camera camera{ 45.f, 1.f, 0.f, 100.f };

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
    ImGui_ImplOpenGL3_Init("#version 450");
    setup_dark_theme();

	camera.set_settings(50.f, 0.2f);
	camera.teleport(500.f, 10.f, 10.f);

	constexpr sim::star star{ 0.001f, 5000.f, 1.f };
	const char* orbit_file = "content/dust_orbits/single_inner_planet_e0.7_Ifree0_efree0_betadistrb1.5_bmin0.001_bmax1.0_peri_orbcorr_morelaunch_dustorbit.txt";
	constexpr float fixed_radiation = 0.35f;
	constexpr int particles_per_orbit = 200;
	constexpr bool thermal_radiation = false;
	constexpr float intensity = 1.4f;
	constexpr float offset = 0.0f;
	constexpr float dust_contribution = 0.1f;

	std::vector<sim::orbit> orbits = sim::load_orbits_from_file(orbit_file, fixed_radiation);
	std::vector<sim::particle> debris_disk = sim::create_debris_disk(orbits, particles_per_orbit, star);

	sim::texture_1d scattering_texture{ "content/textures/scattering.png", 0 };
	sim::texture_1d thermal_texture{ "content/textures/thermal.png", 1 };

	thermal_texture.bind();
	scattering_texture.bind();

	renderer.load_particles(debris_disk.size(), sizeof(sim::particle), debris_disk.data());

	const auto clock = std::chrono::high_resolution_clock{};
	auto last_time = clock.now();

	GLuint render_texture = 0;
	GLuint framebuffer = 0;
	ImVec2 last_viewport_size(0, 0);

	auto create_framebuffer = [](int width, int height, GLuint& framebuffer, GLuint& render_texture) {
		// Delete old framebuffer and texture if they exist
		if (framebuffer != 0) {
			glDeleteFramebuffers(1, &framebuffer);
		}
		if (render_texture != 0) {
			glDeleteTextures(1, &render_texture);
		}

		// Create new framebuffer
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		// Create new texture
		glGenTextures(1, &render_texture);
		glBindTexture(GL_TEXTURE_2D, render_texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, render_texture, 0);
	};

	while (window.is_open())
	{
		using seconds = std::chrono::duration<float, std::ratio<1>>;
		const auto delta_time = std::chrono::duration_cast<seconds>(clock.now() - last_time).count();
		last_time = clock.now();

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
					ImGui::MenuItem("New", "Ctrl+N");
					ImGui::MenuItem("Open", "Ctrl+O");
					ImGui::Separator();
					ImGui::MenuItem("Save", "Ctrl+S");
					ImGui::MenuItem("Save As", "Ctrl+Shift+S");
					ImGui::MenuItem("Export");
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Edit"))
				{
					ImGui::MenuItem("Undo", "Ctrl+Z");
					ImGui::MenuItem("Redo", "Ctrl+Shift+Z", false, false);
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Help"))
				{
					ImGui::MenuItem("About");
					ImGui::MenuItem("Help");
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			ImGui::Begin("Viewport");
			{
				ImVec2 viewport_size = ImGui::GetContentRegionAvail();

				if (viewport_size.x != last_viewport_size.x || viewport_size.y != last_viewport_size.y)
				{
					create_framebuffer((int)viewport_size.x, (int)viewport_size.y, framebuffer, render_texture);
					last_viewport_size = viewport_size;
					
					float aspect_ratio = viewport_size.x / viewport_size.y;
					camera.set_aspect_ratio(aspect_ratio);
				}

				ImGui::Image((void*)(intptr_t)render_texture, viewport_size);
			}
			ImGui::End();

			ImGui::Begin("Properties");
			{
				ImGui::Text("Properties panel");
			}
			ImGui::End();

			ImGui::Begin("Scenes");
			{
				ImGui::Text("Scene view");
			}
			ImGui::End();
		}
		ImGui::End();

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glViewport(0, 0, (int)last_viewport_size.x, (int)last_viewport_size.y);

		camera.update(delta_time);

		renderer.clear();

		shader.use(); // @todo: make it part of the renderer

		// @todo: no need to do that every frame: only do it when it changes
		shader.set_uniform("view_projection", camera.get_view_projection());
		shader.set_uniform("camera_position", camera.get_position());
		shader.set_uniform("thermal_radiation", thermal_radiation);
		shader.set_uniform("intensity", intensity);
		shader.set_uniform("offset", offset);
		shader.set_uniform("dust_contribution", dust_contribution);
		shader.set_uniform("colormap", thermal_radiation ? thermal_texture : scattering_texture);

		renderer.render();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();
	}

	// Cleanup framebuffer and texture
	if (framebuffer != 0) {
		glDeleteFramebuffers(1, &framebuffer);
	}
	if (render_texture != 0) {
		glDeleteTextures(1, &render_texture);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}