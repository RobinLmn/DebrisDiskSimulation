#pragma once

#include <vector>

namespace engine
{
    class widget;

    class editor
    {
    public:
        editor();
        ~editor();

    public:
        template<typename Widget, typename... Args>
        void add_widget(Args&&... args);

        void render();

    private:
        std::vector<widget*> widgets;
    };

    template<typename Widget, typename... Args>
    void editor::add_widget(Args&&... args)
    {
        widgets.push_back(new Widget(std::forward<Args>(args)...));
    }
}

