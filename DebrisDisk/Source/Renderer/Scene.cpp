#include "Scene.h"
#include <glad/glad.h>

namespace DebrisDisk
{
	void RScene::Init()
	{
        float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        Shader = new RShader("Content/VertexShader.vs", "Content/FragmentShader.fs");
	}

	void RScene::Render()
	{
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(Shader->ID);
        // set shader's camera variable
		glBindVertexArray(VAO);

        glEnable(GL_PROGRAM_POINT_SIZE);
        glPointSize(3);
        glDrawArraysInstanced(GL_POINTS, 0, 1, 3);
	}

	void RScene::Terminate()
	{
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
	}
}