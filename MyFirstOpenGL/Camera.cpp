#include "Camera.h"

Camera::Camera()
{
    position = glm::vec3(0.0f, 0.0f, 5.0f);
    localVectorUp = glm::vec3(0.0f, 1.0f, 0.0f);
    fFov = 45.0f;
    fNear = 0.1f;
    fFar = 10.0f;
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), localVectorUp);
}

glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) const
{
    return glm::perspective(glm::radians(fFov), aspectRatio, fNear, fFar);
}