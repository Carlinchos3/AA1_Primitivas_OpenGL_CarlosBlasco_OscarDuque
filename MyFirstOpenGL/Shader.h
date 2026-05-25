#pragma once

#include <GL/glew.h>

class Shader
{
public:
	GLuint CreateProgram(const char* vertexShader, const char* fragmentSource);

};