#include "Ortoedro.h"

Ortoedro::Ortoedro(Mesh* mesh, GLuint shaderProgram)
    : GameObject(mesh, shaderProgram),
    m_velocidadRotacion(1.0f),
    m_escaladoActual(1.0f),
    m_incrementoEscalado(0.01f)
{
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Ortoedro::Update(float deltaTime)
{
    // Rotación en eje Z
    m_rotation.z += m_velocidadRotacion * m_speedMultiplier;

    // Escalado oscilante
    m_escaladoActual += m_incrementoEscalado * m_speedMultiplier;

    if (m_escaladoActual >= S_ESCALADO_MAX)
        m_incrementoEscalado *= -1.f;
    if (m_escaladoActual <= S_ESCALADO_MIN)
        m_incrementoEscalado *= -1.f;

    m_scale = glm::vec3(m_escaladoActual, 1.0f, m_escaladoActual);
}