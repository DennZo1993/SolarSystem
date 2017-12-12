#pragma once

#include <string>

#include <GL/glew.h>


class TShader {
public:
    void LoadVertexShader(const std::string& fileName);
    void LoadFragmentShader(const std::string& fileName);

    void Build();

    void Use() { glUseProgram(ProgramID); }

    GLuint GetProgramID() const { return ProgramID; }

protected:
    std::string Load(const std::string& fileName,
                     const std::string& shaderType);

    void Compile(GLuint shaderId,
                 const std::string& shaderSource,
                 const std::string& shaderType);

    void Link();
    void DestroyShaders();

private:
    GLuint ProgramID;

    GLuint VertexShaderID;
    GLuint FragmentShaderID;
};