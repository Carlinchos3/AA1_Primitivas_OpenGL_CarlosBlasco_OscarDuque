#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera();

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspectRatio) const;
    glm::vec3 m_position;
    glm::vec3 m_localVectorUp;

    float m_fFov;
    float m_fNear;
    float m_fFar;
};