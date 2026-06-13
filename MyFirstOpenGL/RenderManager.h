#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Camera.h"
#include "ShaderManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Cubo.h"
#include "Ortoedro.h"
#include "Piramide.h"

class RenderManager
{
public:

    RenderManager();

    ~RenderManager();

    void Run();

private:

    GLFWwindow* m_window;
    Camera m_camera;
    GLuint m_shaderProgram;
    InputManager* m_inputManager;
    std::vector<GameObject*> m_gameObjects;
    std::vector<Mesh*> m_meshes;

    static constexpr int S_WINDOW_WIDTH = 640;
    static constexpr int S_WINDOW_HEIGHT = 480;

    void InitWindow();

    void InitGLEW();

    void InitShaders();

    void InitScene();

    void Update();

    void Render();

    void Cleanup();

    static void Resize_Window(GLFWwindow* window, int width, int height);
};