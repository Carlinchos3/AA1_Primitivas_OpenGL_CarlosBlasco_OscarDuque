#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Mesh.h"

class GameObject
{
public:

	GameObject(Mesh* mesh, GLuint shaderProgram);

	virtual ~GameObject();

	virtual void Update(float deltaTime) = 0;

	virtual void Draw() const;

	void SetVisible(bool visible);

	bool IsVisible() const;

	void SetSpeedMultiplier(float speed) { m_speedMultiplier = speed; }

protected:

	Mesh* m_mesh;
	GLuint m_shaderProgram;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	bool m_visible;

	float m_speedMultiplier;

	glm::mat4 GetModelMatrix() const;
};