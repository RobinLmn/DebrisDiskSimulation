#version 450 core

#define pi 3.14159265359

uniform mat4 ViewProjectionMat;
uniform vec3 CameraPos;
uniform bool bThermal;
uniform float Intensity;
uniform float Offset;
uniform float DustContribution;

out float MyIntensity;
out float MyAlpha;

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
    return (1.0 - G * G) / (4.0 * pi * pow(1.0 + G * G - 2.0 * G * CosT, 1.5));
};

float HG_Combination(float CosT)
{
    // return 0.7 * HG(CosT, 0.995) + 0.16 * HG(CosT, 0.6) + 0.14 * HG(CosT, 0.02);
    return HG(CosT, 0.5);
}

float PlanckFunction(float T)
{
    return 0.11934 /(exp(14.413/T) - 1);
}

void main()
{
    ParticleData P = Particles.Data[gl_InstanceID];
    gl_Position = ViewProjectionMat * vec4(P.Pos.xyz, 1.0);

    if (bThermal)
    {
        MyIntensity = Offset + Intensity * PlanckFunction(P.Temp);
    }
    else
    {
        float CosT = dot(normalize(P.Pos.xyz), normalize(CameraPos));
        MyIntensity = Offset + Intensity * 1000.0 * HG_Combination(CosT) / (P.Beta * P.Beta * P.Rad2);
    }

    MyAlpha = DustContribution;
}