#pragma once
#include "GameObject.h"

class Ortoedro : public GameObject
{
public:

    Ortoedro(Mesh* mesh, GLuint shaderProgram);
    void Update(float deltaTime) override;

private:

    float velocidadRotacion;
    float escaladoActual;
    float incrementoEscalado;

    float escaladoMax = 2.0f;
    float escaladoMin = 1.0f;
};