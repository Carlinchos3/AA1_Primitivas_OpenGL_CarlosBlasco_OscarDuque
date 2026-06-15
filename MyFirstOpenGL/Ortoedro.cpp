#include "Ortoedro.h"

Ortoedro::Ortoedro(Mesh* mesh, GLuint shaderProgram)
    : GameObject(mesh, shaderProgram),
    velocidadRotacion(1.0f),
    escaladoActual(1.0f),
    incrementoEscalado(0.01f)
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Ortoedro::Update(float deltaTime)
{
    // Rotación en eje Z
    rotation.z += velocidadRotacion * speedMultiplier;

    // Escalado oscilante
    escaladoActual += incrementoEscalado * speedMultiplier;

    //Para que cuando llegue al limite del escalado se invierta
    if (escaladoActual >= escaladoMax)
        incrementoEscalado *= -1.f;
    if (escaladoActual <= escaladoMin)
        incrementoEscalado *= -1.f;

    scale = glm::vec3(escaladoActual, 1.0f, escaladoActual);
}