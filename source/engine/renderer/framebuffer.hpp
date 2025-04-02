#pragma once

namespace engine
{
    class framebuffer
    {
    public:
        framebuffer(const int width, const int height);
        ~framebuffer();
        
    public:
        void bind() const;
        void unbind() const;
        void resize(const int width, const int height);

        unsigned int get_render_texture() const;
    
    private:
        void recreate();
        
    private:
        int width;
        int height;
        unsigned int id;
        unsigned int render_texture;
    };
}
