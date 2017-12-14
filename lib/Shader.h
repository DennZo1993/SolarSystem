#pragma once

#include <string>

#include <GL/glew.h>


class TShaderProgram {
public:
    TShaderProgram() = default;
    ~TShaderProgram();

public:
    void LoadShader(GLenum shaderType, const std::string& fileName);

    void Build();

    void Use() { glUseProgram(ProgramID); }

    GLuint GetProgramID() const { return ProgramID; }

protected:
    GLuint CreateShader(GLenum shaderType, const std::string& fileName);

    std::string LoadSourceFile(const std::string& fileName);

    void CompileSource(GLuint shaderId, const std::string& shaderSource);

    void Link();
    void DestroyShaders();

private:
    GLuint ProgramID { 0 };

    GLuint VertexShaderID         { 0 }; // Required
    GLuint FragmentShaderID       { 0 }; // Required
    GLuint TessControlShaderID    { 0 }; // Optional
    GLuint TessEvaluationShaderID { 0 }; // Optional
    GLuint GeometryShaderID       { 0 }; // Optional
    GLuint ComputeShaderID        { 0 }; // Optional
};