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

	void SetSpeedMultiplier(float speed) { speedMultiplier = speed; }

protected:

	Mesh* mesh;
	GLuint shaderProgram;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	bool visible;

	float speedMultiplier;

	glm::mat4 GetModelMatrix() const;
};