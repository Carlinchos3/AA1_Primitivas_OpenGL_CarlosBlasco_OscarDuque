#pragma once
#include "GameObject.h"

class Ortoedro : public GameObject
{
public:

    Ortoedro(Mesh* mesh, GLuint shaderProgram);
    void Update(float deltaTime) override;

private:

    float m_velocidadRotacion;
    float m_escaladoActual;
    float m_incrementoEscalado;

    static constexpr float S_ESCALADO_MAX = 2.0f;
    static constexpr float S_ESCALADO_MIN = 1.0f;
};