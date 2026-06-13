#pragma once
#include "GameObject.h"

class Cubo : public GameObject
{
public:

    Cubo(Mesh* mesh, GLuint shaderProgram);

    void Update(float deltaTime) override;

private:

    float movimiento;
    float velocidadMovimiento;
    float velocidadRotacion;

    float limiteArriba = 1.0f;
    float limiteAbajo = -1.0f;
};