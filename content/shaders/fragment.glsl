#version 450 core

in float particle_intensity;
in float particle_alpha;

out vec4 frag_color;

uniform sampler1D colormap;
  
void main()
{
    frag_color = vec4(texture(colormap, particle_intensity).xyz, particle_alpha);
}