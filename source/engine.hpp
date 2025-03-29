#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

struct GLFWwindow;

namespace sim 
{
    class window 
    {
    public:
        window(int width, int height, const char* title);
        ~window();

    public:
        void update();
        bool is_open() const;

    private:
        GLFWwindow* native_window;
    };

    class shader
    {
    public:
        shader(const char* vertex_path, const char* fragment_path);
        ~shader();

    public:
        void use() const;
        
        template<typename T>
        void set_uniform(const char* name, const T& value) const;

    private:
        unsigned int id;
    };

    class texture_1d
    {
    public:
        texture_1d(const char* filename, const unsigned int unit);
        ~texture_1d();

    public:
        void bind() const;
        void unbind() const;

        unsigned int get_unit() const;

    private:
        unsigned int id;
        unsigned int unit;
    };

    class renderer 
    {
    public:
        renderer();
        ~renderer();

    public:
        void load_particles(const size_t particle_count, const size_t particle_size, const void* particles);
        void clear();
        void render();

        void create_framebuffer(int width, int height);
        void bind_framebuffer(int width, int height);
        void unbind_framebuffer();
        unsigned int get_render_texture() const { return render_texture; }

    private:
        unsigned int vao;
        unsigned int particle_buffer;
        size_t particle_count;

        unsigned int framebuffer;
        unsigned int render_texture;
    };
}