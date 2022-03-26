#include "Scene.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"

#include "Systems/DebrisDisk.h"
#include <Tracy/Tracy.hpp>
#include "Engine/Log.h"
#include "Engine/Engine.h"

namespace DebrisDisk
{

    RScene::RScene(RCamera* Camera, SDebrisDisk* Disk)
        : Camera(Camera), Disk(Disk)
    {
    }

	void RScene::Init()
	{
        ZoneScoped

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, 0, {}, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(0);
        glBindVertexArray(0);

        glCreateBuffers(1, &ParticleBuffer);

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ParticleBuffer);
        glBufferData(GL_SHADER_STORAGE_BUFFER, Disk->Particles.size() * sizeof(SParticle), Disk->Particles.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        Shader = new RShader("Content/VertexShader.vs", "Content/FragmentShader.fs");

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &ScatteringTexture);
        glBindTexture(GL_TEXTURE_1D, ScatteringTexture);
        LoadTexture("Scattering");

        glGenTextures(1, &ThermalTexture);
        glBindTexture(GL_TEXTURE_1D, ThermalTexture);
        LoadTexture("Thermal");
	}

    void RScene::LoadTexture(std::string Name)
    {
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        int Width, Height, NrChannels;
        unsigned char* TextureData = stbi_load(("Content/" + Name + ".png").c_str(), &Width, &Height, &NrChannels, 0);

        if (TextureData)
        {
            glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, Width, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureData);
        }
        else LOG_ERROR("Failed to log texture");
        stbi_image_free(TextureData);

        glUniform1i(glGetUniformLocation(Shader->ID, Name.c_str()), 0);
    }

	void RScene::Render()
	{
        ZoneScoped
        
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(Shader->ID);
        glUniformMatrix4fv(glGetUniformLocation(Shader->ID, "ViewProjectionMat"), 1, GL_FALSE, glm::value_ptr(Camera->ViewProjectionMat));
        glUniform1f(glGetUniformLocation(Shader->ID, "bThermal"), Camera->bThermal);
        glUniform1f(glGetUniformLocation(Shader->ID, "Intensity"), Camera->Intensity);
        glUniform1f(glGetUniformLocation(Shader->ID, "Offset"), Camera->Offset);
        glUniform1f(glGetUniformLocation(Shader->ID, "DustContribution"), Camera->DustContribution);
        glUniform3f(glGetUniformLocation(Shader->ID, "CameraPos"), Camera->Position.x, Camera->Position.y, Camera->Position.z);
        
        glBindVertexArray(VAO);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ParticleBuffer);
        
        glActiveTexture(GL_TEXTURE0);

        if (Camera->bThermal)
            glBindTexture(GL_TEXTURE_1D, ThermalTexture);
        else
            glBindTexture(GL_TEXTURE_1D, ScatteringTexture);
        
        glEnable(GL_PROGRAM_POINT_SIZE);
        glPointSize(1);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glDrawArraysInstanced(GL_POINTS, 0, 1, Disk->Particles.size());
        
        glBindVertexArray(0);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
	}

	void RScene::Terminate()
	{
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &ParticleBuffer);
	}

    void RScene::Screenshot(std::string Filename)
    {
        // Adapted from https://github.com/quentinplessis/STBI

        const FWindow& Window = FEngine::GetEngine().GetWindow();
        unsigned char* Buffer = (unsigned char*)malloc(Window.Width * Window.Height * 3);
        glReadPixels(0, 0, Window.Width, Window.Height, GL_RGB, GL_UNSIGNED_BYTE, Buffer);
        unsigned char* LastRow = Buffer + (Window.Width * 3 * (Window.Height - 1));
        if (!stbi_write_png(("Content/Screenshots/" + Filename + ".png").c_str(), Window.Width, Window.Height, 3, LastRow, -3 * Window.Width))
            LOG_ERROR("Could not write png.");
        free(Buffer);
    }
}