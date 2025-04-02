#pragma once

namespace engine
{
    class widget
    {
    public:
        virtual ~widget() = default;
        virtual void draw() = 0;
    };
}
