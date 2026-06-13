#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>

struct ShaderProgram
{
    GLuint m_vertexShader = 0;
    GLuint m_geometryShader = 0;
    GLuint m_fragmentShader = 0;
};

class ShaderManager
{
public:

    static GLuint LoadVertexShader(const std::string& filePath);
    static GLuint LoadGeometryShader(const std::string& filePath);
    static GLuint LoadFragmentShader(const std::string& filePath);
    static GLuint CreateProgram(const ShaderProgram& shaders);

private:

    static std::string LoadFile(const std::string& filePath);
    static GLuint CompileShader(const std::string& filePath, GLenum shaderType);
};