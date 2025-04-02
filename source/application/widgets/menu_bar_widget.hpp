#pragma once

#include "engine/editor/widget.hpp"

#include <functional>

namespace app
{
    struct menu_bar_widget_delegates
    {
        std::function<void()> on_new_scene_requested;
        std::function<void(const char*)> on_open_scene_requested;
        std::function<void()> on_export_requested;
    };

    class menu_bar_widget final : public engine::widget
    {
    public:
        explicit menu_bar_widget(menu_bar_widget_delegates&& delegates);

    public:
        virtual void draw() override;

    private:
        menu_bar_widget_delegates delegates;
    };
}

