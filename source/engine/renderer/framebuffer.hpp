#pragma once

namespace engine
{
    class framebuffer
    {
        friend class renderer;
        
    public:
        void bind() const;
        void unbind() const;

        unsigned int get_render_texture() const;
        
    private:
        int width = 0;
        int height = 0;
        unsigned int id = 0;
        unsigned int render_texture = 0;
    };
}
