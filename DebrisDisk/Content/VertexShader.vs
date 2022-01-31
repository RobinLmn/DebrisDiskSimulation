#version 450 core

uniform mat4 ViewProjectionMat;

struct particle_data 
{
    vec4 pos;
};

layout(std430, binding = 0) readonly buffer ParticleBuffer
{
    particle_data data[];
} particles;


void main()
{
  gl_Position = ViewProjectionMat * vec4(particles.data[gl_InstanceID].pos.xyz, 1.0);
}