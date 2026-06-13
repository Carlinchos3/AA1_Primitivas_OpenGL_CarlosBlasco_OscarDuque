#include "Cubo.h"

Cubo::Cubo(Mesh* mesh, GLuint shaderProgram)
    : GameObject(mesh, shaderProgram),
    movimiento(0.0f),
    velocidadMovimiento(0.01f),
    velocidadRotacion(1.0f)
{
    position = glm::vec3(-1.8f, 0.0f, 0.0f);
}

void Cubo::Update(float deltaTime)
{
    // Traslación arriba/abajo
    movimiento += velocidadMovimiento * speedMultiplier;

    if (movimiento >= limiteArriba)
        velocidadMovimiento *= -1.f;
    if (movimiento <= limiteAbajo)
        velocidadMovimiento *= -1.f;

    position.y = movimiento;

    // Rotación en eje Y
    rotation.y += velocidadRotacion * speedMultiplier;
}