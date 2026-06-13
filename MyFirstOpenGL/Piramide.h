#pragma once
#include "GameObject.h"

class Piramide : public GameObject
{
public:

    Piramide(Mesh* mesh, GLuint shaderProgram);

    void Update(float deltaTime) override;

private:

    float movimiento;
    float velocidadMovimiento;
    float velocidadRotacion;

    float limiteArriba = 1.0f;
    float limiteAbajo = -1.0f;
};