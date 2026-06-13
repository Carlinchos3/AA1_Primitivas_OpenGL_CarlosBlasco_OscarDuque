#pragma once
#include "GameObject.h"

class Piramide : public GameObject
{
public:

    Piramide(Mesh* mesh, GLuint shaderProgram);

    void Update(float deltaTime) override;

private:

    float m_movimiento;
    float m_velocidadMovimiento;
    float m_velocidadRotacion;

    static constexpr float S_LIMITE_ARRIBA = 1.0f;
    static constexpr float S_LIMITE_ABAJO = -1.0f;
};