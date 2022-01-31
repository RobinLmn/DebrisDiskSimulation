#pragma once

#include <string>

// From https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader_s.h

namespace DebrisDisk
{
	class RShader
	{
    public:
        RShader(const char* vertexPath, const char* fragmentPath);
        virtual ~RShader() = default;

    private:
        void checkCompileErrors(unsigned int shader, std::string type);

    public:
        unsigned int ID;
	};
}