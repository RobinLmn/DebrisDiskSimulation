#pragma once

#include "engine/editor/widget.hpp"

#include <functional>

namespace app
{
    struct debris_disk_widget_properties
    {
        bool thermal_radiation;
        float intensity;
        float offset;
        float dust_contribution;
    };

    struct camera_widget_properties
    {
        float distance;
        float altitude;
        float azimuth;

        float speed;
        float sensitivity;
    };

    struct properties_widget_delegates
    {
        std::function<void(const debris_disk_widget_properties&)> on_debris_disk_properties_changed;
        std::function<void(const camera_widget_properties&)> on_camera_position_changed;
        std::function<void(const camera_widget_properties&)> on_camera_settings_changed;
        std::function<void()> on_properties_reset_requested;
        std::function<debris_disk_widget_properties()> get_debris_disk_properties;
        std::function<camera_widget_properties()> get_camera_properties;
    };

    class properties_widget final : public engine::widget
    {
    public:
        explicit properties_widget(properties_widget_delegates&& delegates);

    public:
        virtual void draw() override;

    private:
        properties_widget_delegates delegates;
    };
}
