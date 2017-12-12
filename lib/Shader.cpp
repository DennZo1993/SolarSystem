#include "Shader.h"
#include "Exception.h"

#include <sstream>
#include <fstream>
#include <string>


void TShader::LoadVertexShader(const std::string& fileName) {
    std::string type = "vertex";
    std::string source = Load(fileName, type);
    VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    Compile(VertexShaderID, source, type);
}


void TShader::LoadFragmentShader(const std::string& fileName) {
    std::string type = "fragment";
    std::string source = Load(fileName, type);
    FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    Compile(FragmentShaderID, source, type);
}


void TShader::Build() {
    Link();
    DestroyShaders();
}


std::string TShader::Load(const std::string& fileName, const std::string& shaderType) {
    std::ifstream ifs(fileName);
    if (!ifs.is_open())
        throw TShaderException("Failed to load " + shaderType + " shader from " + fileName);

    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}


void TShader::Compile(GLuint shaderId, const std::string& shaderSource, const std::string& shaderType) {
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

        throw TShaderException("Failed to compile " + shaderType + " shader, log: \"" + log + "\"");
    }
}


void TShader::Link() {
    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check
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


void TShader::DestroyShaders() {
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
}