#version 330 core

in float MyIntensity;
out vec4 FragColor;

uniform sampler1D Texture;
  
void main()
{
    FragColor = vec4(texture(Texture, MyIntensity).xyz, 0.3);
}