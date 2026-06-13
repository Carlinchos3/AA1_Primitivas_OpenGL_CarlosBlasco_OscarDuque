#include "RenderManager.h"
#include <iostream>
#include <gtc/type_ptr.hpp>

RenderManager::RenderManager()
    : m_window(nullptr),
    m_shaderProgram(0),
    m_inputManager(nullptr)
{
    InitWindow();
    InitGLEW();
    InitShaders();
    InitScene();
}

RenderManager::~RenderManager()
{
    Cleanup();
}

void RenderManager::InitWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    m_window = glfwCreateWindow(S_WINDOW_WIDTH, S_WINDOW_HEIGHT, "My Engine", NULL, NULL);

    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, Resize_Window);
    glfwMakeContextCurrent(m_window);
}

void RenderManager::InitGLEW()
{
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Error al inicializar GLEW" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void RenderManager::InitShaders()
{
    ShaderProgram program;
    program.m_vertexShader = ShaderManager::LoadVertexShader("VertexShader.glsl");
    program.m_geometryShader = ShaderManager::LoadGeometryShader("GeometryShader.glsl");
    program.m_fragmentShader = ShaderManager::LoadFragmentShader("FragmentShader.glsl");

    m_shaderProgram = ShaderManager::CreateProgram(program);

    glUseProgram(m_shaderProgram);

    glm::mat4 viewMatrix = m_camera.GetViewMatrix();
    glm::mat4 projectionMatrix = m_camera.GetProjectionMatrix((float)S_WINDOW_WIDTH / (float)S_WINDOW_HEIGHT);

    glUniform2f(glGetUniformLocation(m_shaderProgram, "windowSize"), S_WINDOW_WIDTH, S_WINDOW_HEIGHT);
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void RenderManager::InitScene()
{
    // Vértices e índices del cubo
    std::vector<GLfloat> verticeCubo =
    {
        -0.5f, +0.5f, -0.5f,
        +0.5f, +0.5f, -0.5f,
        +0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, +0.5f, +0.5f,
        +0.5f, +0.5f, +0.5f,
        +0.5f, -0.5f, +0.5f,
        -0.5f, -0.5f, +0.5f
    };
    std::vector<GLuint> indiceCubo =
    {
        0,1,2, 0,2,3,
        4,6,5, 4,7,6,
        4,5,1, 4,1,0,
        3,2,6, 3,6,7,
        4,0,3, 4,3,7,
        1,5,6, 1,6,2
    };

    // Vértices e índices del ortoedro
    std::vector<GLfloat> verticeOrtoedro =
    {
        -0.25f, +0.5f, -0.25f,
        +0.25f, +0.5f, -0.25f,
        +0.25f, -0.5f, -0.25f,
        -0.25f, -0.5f, -0.25f,
        -0.25f, +0.5f, +0.25f,
        +0.25f, +0.5f, +0.25f,
        +0.25f, -0.5f, +0.25f,
        -0.25f, -0.5f, +0.25f
    };
    std::vector<GLuint> indiceOrtoedro =
    {
        0,1,2, 0,2,3,
        4,6,5, 4,7,6,
        4,5,1, 4,1,0,
        3,2,6, 3,6,7,
        4,0,3, 4,3,7,
        1,5,6, 1,6,2
    };

    // Vértices e índices de la pirámide
    std::vector<GLfloat> verticePiramide =
    {
        -0.5f, -0.5f, -0.5f,
        +0.5f, -0.5f, -0.5f,
        +0.5f, -0.5f, +0.5f,
        -0.5f, -0.5f, +0.5f,
         0.0f, +0.5f,  0.0f
    };
    std::vector<GLuint> indicePiramide =
    {
        0,2,1, 0,3,2,
        0,1,4,
        1,2,4,
        2,3,4,
        3,0,4
    };

    // Crear mallas
    m_meshes.push_back(new Mesh(verticeCubo, indiceCubo));
    m_meshes.push_back(new Mesh(verticeOrtoedro, indiceOrtoedro));
    m_meshes.push_back(new Mesh(verticePiramide, indicePiramide));

    // Crear GameObjects
    m_gameObjects.push_back(new Cubo(m_meshes[0], m_shaderProgram));
    m_gameObjects.push_back(new Ortoedro(m_meshes[1], m_shaderProgram));
    m_gameObjects.push_back(new Piramide(m_meshes[2], m_shaderProgram));

    // Crear InputManager
    m_inputManager = new InputManager(m_window, m_gameObjects);
}

void RenderManager::Run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();

        m_inputManager->ProcessInput();

        Update();
        Render();

        glFlush();
        glfwSwapBuffers(m_window);
    }
}

void RenderManager::Update()
{
    if (m_inputManager->IsPaused()) return;

    float fTime = static_cast<float>(glfwGetTime());
    glUniform1f(glGetUniformLocation(m_shaderProgram, "time"), fTime);

    float speedMultiplier = m_inputManager->GetSpeedMultiplier();

    for (GameObject* obj : m_gameObjects)
    {
        obj->SetSpeedMultiplier(speedMultiplier);
        obj->Update(speedMultiplier);
    }
}

void RenderManager::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glUseProgram(m_shaderProgram);

    for (GameObject* obj : m_gameObjects)
    {
        obj->Draw();
    }
}

void RenderManager::Cleanup()
{
    for (GameObject* obj : m_gameObjects)
    {
        delete obj;
    }
    m_gameObjects.clear();

    for (Mesh* mesh : m_meshes)
    {
        delete mesh;
    }
    m_meshes.clear();

    delete m_inputManager;

    glUseProgram(0);
    glDeleteProgram(m_shaderProgram);

    glfwTerminate();
}

void RenderManager::Resize_Window(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    RenderManager* manager = static_cast<RenderManager*>(glfwGetWindowUserPointer(window));
    glUniform2f(glGetUniformLocation(manager->m_shaderProgram, "windowSize"), width, height);
}