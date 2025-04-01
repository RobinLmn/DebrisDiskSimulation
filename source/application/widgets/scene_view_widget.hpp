#pragma once

#include "engine/editor/widget.hpp"

#include <functional>
#include <vector>

namespace app
{
    class scene;

    struct scene_view_widget_delegates
    {
        std::function<void(const scene&)> on_scene_selected;
        std::function<const std::vector<scene>&()> get_all_scenes;
    };

    class scene_view_widget final : public engine::widget
    {
    public:
        explicit scene_view_widget(scene_view_widget_delegates&& delegates);

    public:
        virtual void draw() override;

    private:
        scene_view_widget_delegates delegates;
    };
}
