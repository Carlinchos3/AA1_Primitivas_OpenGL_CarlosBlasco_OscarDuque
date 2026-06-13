#include "InputManager.h"
#include <GL/glew.h>

InputManager::InputManager(GLFWwindow* window, std::vector<GameObject*>& gameObjects)
    : m_window(window),
    m_gameObjects(gameObjects),
    m_isPaused(false),
    m_wireframe(false),
    m_tecla1Pulsada(false),
    m_tecla2Pulsada(false),
    m_tecla3Pulsada(false),
    m_tecla4Pulsada(false),
    m_teclaEspacioPulsada(false),
    m_teclaMPulsada(false),
    m_teclaNPulsada(false),
    m_speedMultiplier(1.0f)
{
}

void InputManager::ProcessInput()
{
    ProcessSpace();

    if (!m_isPaused)
    {
        ProcessSpeed();
        ProcessToggles();
    }
}

bool InputManager::IsPaused() const
{
    return m_isPaused;
}

float InputManager::GetSpeedMultiplier() const
{
    return m_speedMultiplier;
}

void InputManager::ProcessSpace()
{
    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS && !m_teclaEspacioPulsada)
    {
        m_teclaEspacioPulsada = true;
        m_isPaused = !m_isPaused;
    }
    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_RELEASE)
    {
        m_teclaEspacioPulsada = false;
    }
}

void InputManager::ProcessSpeed()
{
    if (glfwGetKey(m_window, GLFW_KEY_M) == GLFW_PRESS && !m_teclaMPulsada)
    {
        m_teclaMPulsada = true;
        m_speedMultiplier *= S_INCREMENTO_VELOCIDAD;
    }
    if (glfwGetKey(m_window, GLFW_KEY_M) == GLFW_RELEASE)
        m_teclaMPulsada = false;

    if (glfwGetKey(m_window, GLFW_KEY_N) == GLFW_PRESS && !m_teclaNPulsada)
    {
        m_teclaNPulsada = true;
        m_speedMultiplier *= S_DECREMENTO_VELOCIDAD;
    }
    if (glfwGetKey(m_window, GLFW_KEY_N) == GLFW_RELEASE)
        m_teclaNPulsada = false;
}

void InputManager::ProcessToggles()
{
    // Tecla 1 - Wireframe
    if (glfwGetKey(m_window, GLFW_KEY_1) == GLFW_PRESS && !m_tecla1Pulsada)
    {
        m_tecla1Pulsada = true;
        m_wireframe = !m_wireframe;
        glPolygonMode(GL_FRONT_AND_BACK, m_wireframe ? GL_LINE : GL_FILL);
    }
    if (glfwGetKey(m_window, GLFW_KEY_1) == GLFW_RELEASE)
    {
        m_tecla1Pulsada = false;
    }

    // Tecla 2 - Visibilidad cubo
    if (glfwGetKey(m_window, GLFW_KEY_2) == GLFW_PRESS && !m_tecla2Pulsada)
    {
        m_tecla2Pulsada = true;
        m_gameObjects[0]->SetVisible(!m_gameObjects[0]->IsVisible());
    }
    if (glfwGetKey(m_window, GLFW_KEY_2) == GLFW_RELEASE)
    {
        m_tecla2Pulsada = false;
    }

    // Tecla 3 - Visibilidad ortoedro
    if (glfwGetKey(m_window, GLFW_KEY_3) == GLFW_PRESS && !m_tecla3Pulsada)
    {
        m_tecla3Pulsada = true;
        m_gameObjects[1]->SetVisible(!m_gameObjects[1]->IsVisible());
    }
    if (glfwGetKey(m_window, GLFW_KEY_3) == GLFW_RELEASE)
    {
        m_tecla3Pulsada = false;
    }

    // Tecla 4 - Visibilidad pirámide
    if (glfwGetKey(m_window, GLFW_KEY_4) == GLFW_PRESS && !m_tecla4Pulsada)
    {
        m_tecla4Pulsada = true;
        m_gameObjects[2]->SetVisible(!m_gameObjects[2]->IsVisible());
    }
    if (glfwGetKey(m_window, GLFW_KEY_4) == GLFW_RELEASE)
    {
        m_tecla4Pulsada = false;
    }
}