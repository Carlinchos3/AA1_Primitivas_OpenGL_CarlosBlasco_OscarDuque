#include "Piramide.h"

Piramide::Piramide(Mesh* mesh, GLuint shaderProgram)
    : GameObject(mesh, shaderProgram),
    m_movimiento(0.0f),
    m_velocidadMovimiento(0.01f),
    m_velocidadRotacion(1.0f)
{
    m_position = glm::vec3(1.8f, 0.0f, 0.0f);
}

void Piramide::Update(float deltaTime)
{
    // Traslación arriba/abajo
    m_movimiento += m_velocidadMovimiento * m_speedMultiplier;

    if (m_movimiento >= S_LIMITE_ARRIBA)
        m_velocidadMovimiento *= -1;
    if (m_movimiento <= S_LIMITE_ABAJO)
        m_velocidadMovimiento  *= -1;

    m_position.y = m_movimiento;

    // Rotación en eje X e Y
    m_rotation.x += m_velocidadRotacion * m_speedMultiplier;
    m_rotation.y += m_velocidadRotacion * m_speedMultiplier;
}