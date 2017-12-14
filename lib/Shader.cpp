#include "Shader.h"
#include "Exception.h"

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>


TShaderProgram::~TShaderProgram()
{
    DestroyShaders();
}


void TShaderProgram::LoadShader(GLenum shaderType, const std::string& fileName)
{
    switch (shaderType) {
    case GL_VERTEX_SHADER:
        VertexShaderID = CreateShader(shaderType, fileName);
        break;

    case GL_FRAGMENT_SHADER:
        FragmentShaderID = CreateShader(shaderType, fileName);
        break;

    case GL_TESS_CONTROL_SHADER:
        TessControlShaderID = CreateShader(shaderType, fileName);
        break;

    case GL_TESS_EVALUATION_SHADER:
        TessEvaluationShaderID = CreateShader(shaderType, fileName);
        break;

    case GL_GEOMETRY_SHADER:
        GeometryShaderID = CreateShader(shaderType, fileName);
        break;

    case GL_COMPUTE_SHADER:
        ComputeShaderID = CreateShader(shaderType, fileName);
        break;

    default:
        throw TShaderException("Unsupported shader type: " +
                               std::to_string(static_cast<int>(shaderType)));
    } // switch (shaderType)
}


void TShaderProgram::Build()
{
    Link();
    DestroyShaders();
}


GLuint TShaderProgram::CreateShader(GLenum shaderType, const std::string& fileName)
{
    std::string source = LoadSourceFile(fileName);

    GLuint id = glCreateShader(shaderType);
    if (!id)
        throw TShaderException("Failed to create shader!");

    CompileSource(id, source);
    return id;
}


std::string TShaderProgram::LoadSourceFile(const std::string& fileName)
{
    std::ifstream ifs(fileName);
    if (!ifs.is_open())
        throw TShaderException("Failed to load shader from " + fileName);

    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}


void TShaderProgram::CompileSource(GLuint shaderId, const std::string& shaderSource)
{
    const char* shaderSourcePtr = shaderSource.c_str();
    glShaderSource(shaderId, 1, &shaderSourcePtr, nullptr);
    glCompileShader(shaderId);

    // Check
    GLint checkSuccessful;
    int infoLogLength;

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &checkSuccessful);
    if (!checkSuccessful) {
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::string log(infoLogLength + 1, '\0');
        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, &log[0]);

        throw TShaderException("Failed to compile shader, log: \"" + log + "\"");
    }
}


void TShaderProgram::Link() {
    ProgramID = glCreateProgram();
    if (!ProgramID)
        throw TShaderException("Failed to create shader program!");

    // Attach shaders that are present. Keep in mind that some of them
    // are required.
    if (!VertexShaderID)
        throw TShaderException("Failed to link shader program, vertex shader is not loaded!");
    glAttachShader(ProgramID, VertexShaderID);

    if (!FragmentShaderID)
        throw TShaderException("Failed to link shader program, fragment shader is not loaded!");
    glAttachShader(ProgramID, FragmentShaderID);

    if (TessControlShaderID)
        glAttachShader(ProgramID, TessControlShaderID);

    if (TessEvaluationShaderID)
        glAttachShader(ProgramID, TessEvaluationShaderID);

    if (GeometryShaderID)
        glAttachShader(ProgramID, GeometryShaderID);

    if (ComputeShaderID)
        glAttachShader(ProgramID, ComputeShaderID);

    // Link.
    glLinkProgram(ProgramID);

    // Check.
    GLint checkSuccessful;
    int infoLogLength;
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &checkSuccessful);
    if (!checkSuccessful) {
        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::string log(infoLogLength + 1, '\0');
        glGetProgramInfoLog(ProgramID, infoLogLength, nullptr, &log[0]);
        
        throw TShaderException("Failed to link shader program, log: \"" + log + "\"");
    }
}


void TShaderProgram::DestroyShaders() {
    if (!ProgramID)
        return;

    if (VertexShaderID) {
        glDetachShader(ProgramID, VertexShaderID);
        glDeleteShader(VertexShaderID);
    }

    if (FragmentShaderID) {
        glDetachShader(ProgramID, FragmentShaderID);
        glDeleteShader(FragmentShaderID);
    }

    if (TessControlShaderID) {
        glDetachShader(ProgramID, TessControlShaderID);
        glDeleteShader(TessControlShaderID);
    }

    if (TessEvaluationShaderID) {
        glDetachShader(ProgramID, TessEvaluationShaderID);
        glDeleteShader(TessEvaluationShaderID);
    }

    if (GeometryShaderID) {
        glDetachShader(ProgramID, GeometryShaderID);
        glDeleteShader(GeometryShaderID);
    }

    if (ComputeShaderID) {
        glDetachShader(ProgramID, ComputeShaderID);
        glDeleteShader(ComputeShaderID);
    }
}