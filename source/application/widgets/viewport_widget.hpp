#pragma once

#include "engine/editor/widget.hpp"

#include <functional>

namespace app
{
    struct info_widget_properties
    {
        size_t particle_count = 0;
        float fps = 0.0f;
    };

    struct viewport_widget_delegates
    {
        std::function<unsigned int(int, int)> request_draw;
        std::function<info_widget_properties()> get_info_widget_properties;
    };

    class viewport_widget final : public engine::widget
    {
    public:
        explicit viewport_widget(viewport_widget_delegates&& delegates);

    public:
        virtual void draw() override;

    private:
        bool show_info = false;
        viewport_widget_delegates delegates;
    }; 
}
