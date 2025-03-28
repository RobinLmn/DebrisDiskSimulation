#include <engine.hpp>
#include <input_manager.hpp>
#include <log.hpp>
#include <camera.hpp>
#include <simulation.hpp>

#include <vector>
#include <chrono>

#include <glm/glm.hpp>

int main()
{
	sim::initialize_logger();

	sim::window window{ 800, 800, "Particle Renderer" };
	sim::renderer renderer;
	sim::shader shader{ "content/shaders/vertex.glsl", "content/shaders/fragment.glsl" };
	sim::camera camera{ 45.f, 1.f, 0.f, 100.f };

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

	while (window.is_open())
	{
		using seconds = std::chrono::duration<float, std::ratio<1>>;
		const auto delta_time = std::chrono::duration_cast<seconds>(clock.now() - last_time).count();
		last_time = clock.now();

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
		window.update();
	}

	return 0;
}