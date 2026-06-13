#include "ShaderManager.h"
#include <fstream>
#include <iostream>

std::string ShaderManager::LoadFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    std::string fileContent;
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "No se ha podido abrir el archivo: " << filePath << std::endl;
        std::exit(EXIT_FAILURE);
    }

    while (std::getline(file, line))
    {
        fileContent += line + "\n";
    }

    file.close();
    return fileContent;
}

GLuint ShaderManager::CompileShader(const std::string& filePath, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    std::string sShaderCode = LoadFile(filePath);
    const char* cShaderSource = sShaderCode.c_str();

    glShaderSource(shader, 1, &cShaderSource, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success)
    {
        return shader;
    }
    else
    {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(shader, logLength, nullptr, errorLog.data());

        std::cerr << "Error al compilar el shader: " << errorLog.data() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

GLuint ShaderManager::LoadVertexShader(const std::string& filePath)
{
    return CompileShader(filePath, GL_VERTEX_SHADER);
}

GLuint ShaderManager::LoadGeometryShader(const std::string& filePath)
{
    return CompileShader(filePath, GL_GEOMETRY_SHADER);
}

GLuint ShaderManager::LoadFragmentShader(const std::string& filePath)
{
    return CompileShader(filePath, GL_FRAGMENT_SHADER);
}

GLuint ShaderManager::CreateProgram(const ShaderProgram& shaders)
{
    GLuint program = glCreateProgram();

    if (shaders.vertexShader != 0)   glAttachShader(program, shaders.vertexShader);
    if (shaders.geometryShader != 0) glAttachShader(program, shaders.geometryShader);
    if (shaders.fragmentShader != 0) glAttachShader(program, shaders.fragmentShader);

    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (success)
    {
        if (shaders.vertexShader != 0)   glDetachShader(program, shaders.vertexShader);
        if (shaders.geometryShader != 0) glDetachShader(program, shaders.geometryShader);
        if (shaders.fragmentShader != 0) glDetachShader(program, shaders.fragmentShader);

        return program;
    }
    else
    {
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> errorLog(logLength);
        glGetProgramInfoLog(program, logLength, nullptr, errorLog.data());

        std::cerr << "Error al linkar el programa: " << errorLog.data() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}