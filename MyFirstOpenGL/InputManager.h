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

    GLFWwindow* window;
    std::vector<GameObject*>& gameObjects;

    bool  isPaused;
    bool  wireframe;

    bool  tecla1Pulsada;
    bool  tecla2Pulsada;
    bool  tecla3Pulsada;
    bool  tecla4Pulsada;
    bool  teclaEspacioPulsada;

    bool teclaMPulsada;
    bool teclaNPulsada;

    float speedMultiplier;

    float incrementoVelocidad = 1.1f;
    float decrementoVelocidad = 0.9f;

    void ProcessSpace();

    void ProcessSpeed();

    void ProcessToggles();
};