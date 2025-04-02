#pragma once

#include "engine/core/window.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/framebuffer.hpp"
#include "engine/renderer/texture.hpp"
#include "engine/editor/editor.hpp"
#include "engine/renderer/shader.hpp"

#include "application/simulation/camera.hpp"
#include "application/simulation/scene.hpp"

namespace app
{
    struct debris_disk_widget_properties;
    struct camera_widget_properties;
    struct info_widget_properties;
    class scene;
}

class application
{
public:
    application();

public:
    void run();

private:
    void on_new_scene_requested();  
    void on_open_scene_requested(const char* filename);
    void on_export_requested();

    void on_scene_created(app::scene&& scene);
    bool should_popup_new_scene_window();

    void on_properties_reset_requested();
    void on_debris_disk_properties_changed(const app::debris_disk_widget_properties& properties);
    void on_camera_position_changed(const app::camera_widget_properties& properties);
    void on_camera_settings_changed(const app::camera_widget_properties& properties);
    app::debris_disk_widget_properties get_debris_disk_properties();
    app::camera_widget_properties get_camera_properties();

    const std::vector<app::scene>& get_all_scenes();
    void on_scene_selected(const app::scene& scene);

    unsigned int on_draw_requested(int width, int height);
    app::info_widget_properties get_info_widget_properties();

    void on_camera_moved();

    void set_debris_disk_uniforms();
    void set_camera_uniforms();

private:    
    engine::window window;
    engine::renderer renderer;
    engine::shader shader;
    engine::editor editor;

    app::camera camera;

    app::scene_hierarchy scene_hierarchy;

    engine::texture_1d scattering_texture;
    engine::texture_1d thermal_texture;

private:
    engine::framebuffer framebuffer;
    glm::vec2 last_viewport_size;

    bool should_take_screenshot = false;
    bool show_new_scene_window = false;

    bool thermal_radiation = false;
    float intensity = 1.4f;
    float offset = 0.0f;
    float dust_contribution = 0.1f;

    float delta_time = 0.0f;
};
