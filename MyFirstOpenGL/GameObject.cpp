#include "GameObject.h"

GameObject::GameObject(Mesh* mesh, GLuint shaderProgram)
    : m_mesh(mesh),
    m_shaderProgram(shaderProgram),
    m_position(glm::vec3(0.0f)),
    m_rotation(glm::vec3(0.0f)),
    m_scale(glm::vec3(1.0f)),
    m_visible(true),
    m_speedMultiplier(1.0f)
{
}

GameObject::~GameObject()
{
}

void GameObject::Draw() const
{
    if (!m_visible) return;

    glm::mat4 model = GetModelMatrix();
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "Model"), 1, GL_FALSE, glm::value_ptr(model));
    m_mesh->Draw();
}

void GameObject::SetVisible(bool visible)
{
    m_visible = visible;
}

bool GameObject::IsVisible() const
{
    return m_visible;
}

glm::mat4 GameObject::GetModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);
    model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, m_scale);
    return model;
}