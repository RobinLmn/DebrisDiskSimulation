#version 450 core

#define M_PI 3.14159265359

uniform mat4 ViewProjectionMat;
uniform vec3 CameraPos;
uniform float MaxBeta;
uniform float MaxRad2;
uniform bool bThermal;

out float MyIntensity;

struct ParticleData 
{
    vec4 Pos;
    float Rad2;
    float Beta;
    float Temp;
};

layout(std140, binding = 0) readonly buffer ParticleBuffer
{
    ParticleData Data[];
} Particles;

float HG(float CosT, float G)
{
    return (1.0 - G * G) / (4.0 * M_PI * pow(1.0 + G * G - 2.0 * G * CosT, 1.5));
};

float HG_Combination(float CosT)
{
    return 0.7 * HG(-CosT, 0.995) + 0.16 * HG(-CosT, 0.6) + 0.14 * HG(-CosT, 0.02);
}

void main()
{
    ParticleData P = Particles.Data[gl_InstanceID];
    gl_Position = ViewProjectionMat * vec4(P.Pos.xyz, 1.0);

    if (bThermal)
    {
        MyIntensity = 0.015 * P.Temp;;
    }
    else
    {
        float CosT = dot(normalize(P.Pos.xyz), normalize(CameraPos));
        MyIntensity = 5000.0 * HG_Combination(-CosT) / (P.Beta * P.Beta * P.Rad2);
    }
}