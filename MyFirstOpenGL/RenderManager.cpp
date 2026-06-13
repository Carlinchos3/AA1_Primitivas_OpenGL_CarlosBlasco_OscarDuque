#include "RenderManager.h"
#include <iostream>
#include <gtc/type_ptr.hpp>

RenderManager::RenderManager()
    : window(nullptr),
    shaderProgram(0),
    inputManager(nullptr)
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

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Engine", NULL, NULL);

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, Resize_Window);
    glfwMakeContextCurrent(window);
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
    program.vertexShader = ShaderManager::LoadVertexShader("VertexShader.glsl");
    program.geometryShader = ShaderManager::LoadGeometryShader("GeometryShader.glsl");
    program.fragmentShader = ShaderManager::LoadFragmentShader("FragmentShader.glsl");

    shaderProgram = ShaderManager::CreateProgram(program);

    glUseProgram(shaderProgram);

    glm::mat4 viewMatrix = camera.GetViewMatrix();
    glm::mat4 projectionMatrix = camera.GetProjectionMatrix((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);

    glUniform2f(glGetUniformLocation(shaderProgram, "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
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
    meshes.push_back(new Mesh(verticeCubo, indiceCubo));
    meshes.push_back(new Mesh(verticeOrtoedro, indiceOrtoedro));
    meshes.push_back(new Mesh(verticePiramide, indicePiramide));

    // Crear GameObjects
    gameObjects.push_back(new Cubo(meshes[0], shaderProgram));
    gameObjects.push_back(new Ortoedro(meshes[1], shaderProgram));
    gameObjects.push_back(new Piramide(meshes[2], shaderProgram));

    // Crear InputManager
    inputManager = new InputManager(window, gameObjects);
}

void RenderManager::Run()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        inputManager->ProcessInput();

        Update();
        Render();

        glFlush();
        glfwSwapBuffers(window);
    }
}

void RenderManager::Update()
{
    if (inputManager->IsPaused()) return;

    float fTime = static_cast<float>(glfwGetTime());
    glUniform1f(glGetUniformLocation(shaderProgram, "time"), fTime);

    float speedMultiplier = inputManager->GetSpeedMultiplier();

    for (GameObject* obj : gameObjects)
    {
        obj->SetSpeedMultiplier(speedMultiplier);
        obj->Update(speedMultiplier);
    }
}

void RenderManager::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glUseProgram(shaderProgram);

    for (GameObject* obj : gameObjects)
    {
        obj->Draw();
    }
}

void RenderManager::Cleanup()
{
    for (GameObject* obj : gameObjects)
    {
        delete obj;
    }
    gameObjects.clear();

    for (Mesh* mesh : meshes)
    {
        delete mesh;
    }
    meshes.clear();

    delete inputManager;

    glUseProgram(0);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
}

void RenderManager::Resize_Window(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    RenderManager* manager = static_cast<RenderManager*>(glfwGetWindowUserPointer(window));
    glUniform2f(glGetUniformLocation(manager->shaderProgram, "windowSize"), width, height);
}