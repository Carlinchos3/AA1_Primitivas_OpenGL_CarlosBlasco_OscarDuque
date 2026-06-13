#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera();

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspectRatio) const;
    glm::vec3 position;
    glm::vec3 localVectorUp;

    float fFov;
    float fNear;
    float fFar;
};