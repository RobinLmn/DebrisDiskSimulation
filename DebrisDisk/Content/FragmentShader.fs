#version 330 core

in float MyIntensity;
in float MyAlpha;
out vec4 FragColor;

uniform sampler1D Texture;
  
void main()
{
    FragColor = vec4(texture(Texture, MyIntensity).xyz, MyAlpha);
}