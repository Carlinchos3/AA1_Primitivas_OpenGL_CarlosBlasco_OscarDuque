#version 440 core

layout(location = 0) in vec3 posicion;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
    gl_Position = Projection * View * Model * vec4(posicion, 1.0);
}