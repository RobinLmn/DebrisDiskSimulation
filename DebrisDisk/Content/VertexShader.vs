#version 450 core

#define M_PI 3.14159265359

uniform mat4 ViewProjectionMat;
uniform vec3 CameraPos;

out float MyIntensity;

struct ParticleData 
{
    vec4 Pos;
    float Rad2;
    float Beta;
};

layout(std140, binding = 0) readonly buffer ParticleBuffer
{
    ParticleData Data[];
} Particles;

float HG(float CosT)
{
    float G = 0.5;
	return (1.0 - G * G) / (4.0 * M_PI * pow(1.0 + G * G - 2.0 * G * CosT, 1.5));
};

void main()
{
    ParticleData P = Particles.Data[gl_InstanceID];
    gl_Position = ViewProjectionMat * vec4(P.Pos.xyz, 1.0);

    float CosT = dot(normalize(P.Pos.xyz), normalize(CameraPos));
    MyIntensity = 5000.0 * HG(-CosT) / (P.Beta * P.Beta * P.Rad2);
}