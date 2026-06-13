#include "Camera.h"

Camera::Camera()
{
    m_position = glm::vec3(0.0f, 0.0f, 5.0f);
    m_localVectorUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_fFov = 45.0f;
    m_fNear = 0.1f;
    m_fFar = 10.0f;
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(m_position, glm::vec3(0.0f, 0.0f, 0.0f), m_localVectorUp);
}

glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) const
{
    return glm::perspective(glm::radians(m_fFov), aspectRatio, m_fNear, m_fFar);
}