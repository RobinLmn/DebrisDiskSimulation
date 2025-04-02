#version 450 core

#define pi 3.14159265359

uniform mat4 view_projection;
uniform vec3 camera_position;
uniform bool thermal_radiation;
uniform float intensity;
uniform float offset;
uniform float dust_contribution;

out float particle_intensity;
out float particle_alpha;

struct particle_data 
{
    vec4 position;
    float rad2;
    float beta;
    float temp;
};

layout(std140, binding = 0) readonly buffer particle_buffer
{
    particle_data data[];
} particles;

float HG(float cosT, float G)
{
    return (1.0 - G * G) / (4.0 * pi * pow(1.0 + G * G - 2.0 * G * cosT, 1.5));
};

float HG_combination(float cosT)
{
    return 0.7 * HG(cosT, 0.995) + 0.16 * HG(cosT, 0.6) + 0.14 * HG(cosT, 0.02);
}

float planck_function(float T)
{
    return 0.11934 /(exp(14.413/T) - 1);
}

void main()
{
    particle_data particle = particles.data[gl_InstanceID];
    gl_Position = view_projection * vec4(particle.position.xyz, 1.0);

    if (thermal_radiation)
    {
        particle_intensity = offset + intensity * planck_function(particle.temp);
    }
    else
    {
        float cosT = dot(normalize(particle.position.xyz), normalize(camera_position));
        particle_intensity = offset + intensity * 1000 * HG(cosT, 0.5) / (particle.beta * particle.beta * particle.rad2);
    }

    particle_alpha = dust_contribution;
}