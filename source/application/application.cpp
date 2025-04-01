#include "application.hpp"

#include <chrono>

#include "engine/core/log.hpp"

#include "utils/file_utility.hpp"

#include "application/widgets/menu_bar_widget.hpp"
#include "application/widgets/new_scene_widget.hpp"
#include "application/widgets/properties_widget.hpp"
#include "application/widgets/scene_view_widget.hpp"
#include "application/widgets/viewport_widget.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

application::application()
    : window{ 1920, 1080, "Debris Disk Simulation" }
    , renderer{}
    , editor{}
    , scattering_texture{ "content/textures/scattering.png", 0 }
    , thermal_texture{ "content/textures/thermal.png", 1 }
    , shader{ "content/shaders/vertex.glsl", "content/shaders/fragment.glsl" }
    , camera{ 45.f, 1.f, 0.f, 100.f }
{
    editor.add_widget<app::menu_bar_widget>(app::menu_bar_widget_delegates{
        [this]() { on_new_scene_requested(); },
        [this](const char* filename) { on_open_scene_requested(filename); },
        [this]() { on_export_requested(); }
    });

    editor.add_widget<app::new_scene_widget>(app::new_scene_widget_delegates{
        [this](app::scene&& scene) { on_scene_created(std::move(scene)); },
        [this]() { return should_popup_new_scene_window(); }
    });

    editor.add_widget<app::properties_widget>(app::properties_widget_delegates{
        [this](const app::debris_disk_widget_properties& properties) { on_debris_disk_properties_changed(properties); },
        [this](const app::camera_widget_properties& properties) { on_camera_position_changed(properties); },
        [this](const app::camera_widget_properties& properties) { on_camera_settings_changed(properties); },
        [this]() { on_properties_reset_requested(); },
        [this]() { return get_debris_disk_properties(); },
        [this]() { return get_camera_properties(); }
    });

    editor.add_widget<app::scene_view_widget>(app::scene_view_widget_delegates{
        [this](const app::scene& scene) { on_scene_selected(scene); },
        [this]() -> const std::vector<app::scene>& { return get_all_scenes(); }
    });

    editor.add_widget<app::viewport_widget>(app::viewport_widget_delegates{
        [this](int width, int height) { return on_draw_requested(width, height); },
        [this]() { return get_info_widget_properties(); }
    });
}

void application::run()
{
    camera.set_settings(50.f, 0.2f);
    camera.teleport(500.f, 0.f, 90.f);

    scattering_texture.bind();
    thermal_texture.bind();

    const auto clock = std::chrono::high_resolution_clock{};
    auto last_time = clock.now();

    while (window.is_open())
    {
        using seconds = std::chrono::duration<float, std::ratio<1>>;
        
        delta_time = std::chrono::duration_cast<seconds>(clock.now() - last_time).count();
        last_time = clock.now();

        camera.update(delta_time);

        editor.render();

        window.update();
    }
}

unsigned int application::on_draw_requested(int width, int height) // @todo: wrap this in a viewport class?
{
    if (width != last_viewport_size.x || height != last_viewport_size.y)
    {
        framebuffer = renderer.create_framebuffer(width, height);
        last_viewport_size = { width, height };

        float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
        camera.set_aspect_ratio(aspect_ratio);
    }

    framebuffer.bind();

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

    if (should_take_screenshot)
    {
        const std::vector<unsigned char>& buffer = renderer.read_pixels(width, height);

        const unsigned char* last_row = buffer.data() + (width * 4 * (height - 1));

        std::string filename = utils::new_file_dialog("debris_disk.png", "", "Png Files\0*.png\0");
        stbi_write_png(filename.c_str(), width, height, 4, last_row, -4 * width);

        should_take_screenshot = false;
    }

    framebuffer.unbind();

    return framebuffer.get_render_texture();
}

void application::on_new_scene_requested()
{
    show_new_scene_window = true;
}

void application::on_open_scene_requested(const char* filename)
{
    app::scene new_scene{ filename };
    renderer.load_particles(new_scene.get_particles().size(), sizeof(app::particle), new_scene.get_particles().data());

    scene_hierarchy.add(std::move(new_scene));
}

void application::on_export_requested()
{
    should_take_screenshot = true;
}

void application::on_scene_created(app::scene&& new_scene)
{
    renderer.load_particles(new_scene.get_particles().size(), sizeof(app::particle), new_scene.get_particles().data());
    scene_hierarchy.add(std::move(new_scene));
}

bool application::should_popup_new_scene_window()
{
    if (show_new_scene_window)
    {
        show_new_scene_window = false;
        return true;
    }

    return false;
}

void application::on_properties_reset_requested()
{
    intensity = 1.4f;
    offset = 0.0f;
    dust_contribution = 0.1f;

    camera.teleport(500.0f, 0.0f, 90.0f);
    camera.set_settings(50.0f, 0.2f);
}

void application::on_debris_disk_properties_changed(const app::debris_disk_widget_properties& properties)
{
    thermal_radiation = properties.thermal_radiation;
    intensity = properties.intensity;
    offset = properties.offset;
    dust_contribution = properties.dust_contribution;
}

void application::on_camera_position_changed(const app::camera_widget_properties& properties)
{
    camera.teleport(properties.distance, properties.azimuth, properties.altitude);
}

void application::on_camera_settings_changed(const app::camera_widget_properties& properties)
{
    camera.set_settings(properties.speed, properties.sensitivity);
}

app::debris_disk_widget_properties application::get_debris_disk_properties()
{
    return { thermal_radiation, intensity, offset, dust_contribution };
}

app::camera_widget_properties application::get_camera_properties()
{
    return { camera.get_distance(), camera.get_altitude(), camera.get_azimuth(), camera.get_speed(), camera.get_sensitivity() };
}

const std::vector<app::scene>& application::get_all_scenes()
{
    return scene_hierarchy.get_all_scenes();
}

void application::on_scene_selected(const app::scene& scene)
{
    renderer.load_particles(scene.get_particles().size(), sizeof(app::particle), scene.get_particles().data());
}

app::info_widget_properties application::get_info_widget_properties()
{
    return { renderer.get_particle_count(), 1.0f / delta_time };
}