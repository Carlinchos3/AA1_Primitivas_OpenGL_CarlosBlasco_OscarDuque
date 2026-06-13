#include "Piramide.h"

Piramide::Piramide(Mesh* mesh, GLuint shaderProgram)
    : GameObject(mesh, shaderProgram),
    movimiento(0.0f),
    velocidadMovimiento(0.01f),
    velocidadRotacion(1.0f)
{
    position = glm::vec3(1.8f, 0.0f, 0.0f);
}

void Piramide::Update(float deltaTime)
{
    // Traslación arriba/abajo
    movimiento += velocidadMovimiento * speedMultiplier;

    if (movimiento >= limiteArriba)
        velocidadMovimiento *= -1;
    if (movimiento <= limiteAbajo)
        velocidadMovimiento  *= -1;

    position.y = movimiento;

    // Rotación en eje X e Y
    rotation.x += velocidadRotacion * speedMultiplier;
    rotation.y += velocidadRotacion * speedMultiplier;
}