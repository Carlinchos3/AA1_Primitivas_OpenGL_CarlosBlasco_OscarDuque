#include "InputManager.h"
#include <GL/glew.h>

InputManager::InputManager(GLFWwindow* window, std::vector<GameObject*>& gameObjects)
    : window(window),
    gameObjects(gameObjects),
    isPaused(false),
    wireframe(false),
    tecla1Pulsada(false),
    tecla2Pulsada(false),
    tecla3Pulsada(false),
    tecla4Pulsada(false),
    teclaEspacioPulsada(false),
    teclaMPulsada(false),
    teclaNPulsada(false),
    speedMultiplier(1.0f)
{
}

void InputManager::ProcessInput()
{
    ProcessSpace();

    if (!isPaused)
    {
        ProcessSpeed();
        ProcessToggles();
    }
}

bool InputManager::IsPaused() const
{
    return isPaused;
}

float InputManager::GetSpeedMultiplier() const
{
    return speedMultiplier;
}

void InputManager::ProcessSpace()
{
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !teclaEspacioPulsada)
    {
         teclaEspacioPulsada = true;
         isPaused = !isPaused;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
    {
        teclaEspacioPulsada = false;
    }
}

void InputManager::ProcessSpeed()
{
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && !teclaMPulsada)
    {
        teclaMPulsada = true;
        speedMultiplier *= incrementoVelocidad;
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE)
        teclaMPulsada = false;

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && !teclaNPulsada)
    {
        teclaNPulsada = true;
        speedMultiplier *= decrementoVelocidad;
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE)
        teclaNPulsada = false;
}

void InputManager::ProcessToggles()
{
    // Tecla 1 - Wireframe
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !tecla1Pulsada)
    {
        tecla1Pulsada = true;
        wireframe = !wireframe;
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE)
    {
        tecla1Pulsada = false;
    }

    // Tecla 2 - Visibilidad cubo
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && !tecla2Pulsada)
    {
        tecla2Pulsada = true;
        gameObjects[0]->SetVisible(!gameObjects[0]->IsVisible());
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_RELEASE)
    {
        tecla2Pulsada = false;
    }

    // Tecla 3 - Visibilidad ortoedro
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && !tecla3Pulsada)
    {
        tecla3Pulsada = true;
        gameObjects[1]->SetVisible(!gameObjects[1]->IsVisible());
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_RELEASE)
    {
        tecla3Pulsada = false;
    }

    // Tecla 4 - Visibilidad pirámide
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && !tecla4Pulsada)
    {
        tecla4Pulsada = true;
        gameObjects[2]->SetVisible(!gameObjects[2]->IsVisible());
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_RELEASE)
    {
        tecla4Pulsada = false;
    }
}