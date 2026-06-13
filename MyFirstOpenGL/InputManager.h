#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <vector>
#include "GameObject.h"

class InputManager
{
public:

    InputManager(GLFWwindow* window, std::vector<GameObject*>& gameObjects);

    void ProcessInput();

    bool IsPaused() const;

    float GetSpeedMultiplier() const;

private:

    GLFWwindow* m_window;
    std::vector<GameObject*>& m_gameObjects;

    bool  m_isPaused;
    bool  m_wireframe;

    bool  m_tecla1Pulsada;
    bool  m_tecla2Pulsada;
    bool  m_tecla3Pulsada;
    bool  m_tecla4Pulsada;
    bool  m_teclaEspacioPulsada;

    float m_speedMultiplier;

    static constexpr float S_INCREMENTO_VELOCIDAD = 1.1f;
    static constexpr float S_DECREMENTO_VELOCIDAD = 0.9f;

    void ProcessSpace();

    void ProcessSpeed();

    void ProcessToggles();
};