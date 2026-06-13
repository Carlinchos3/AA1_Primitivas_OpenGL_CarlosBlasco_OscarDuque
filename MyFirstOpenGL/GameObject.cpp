#include "GameObject.h"

GameObject::GameObject(Mesh* mesh, GLuint shaderProgram)
    : mesh(mesh),
    shaderProgram(shaderProgram),
    position(glm::vec3(0.0f)),
    rotation(glm::vec3(0.0f)),
    scale(glm::vec3(1.0f)),
    visible(true),
    speedMultiplier(1.0f)
{
}

GameObject::~GameObject()
{
}

void GameObject::Draw() const
{
    if (!visible) return;

    glm::mat4 model = GetModelMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "Model"), 1, GL_FALSE, glm::value_ptr(model));
    mesh->Draw();
}

void GameObject::SetVisible(bool isVisible)
{
    visible = isVisible;
}

bool GameObject::IsVisible() const
{
    return visible;
}

glm::mat4 GameObject::GetModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    return model;
}