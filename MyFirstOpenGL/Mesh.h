#pragma once
#include <GL/glew.h>
#include <vector>


class Mesh {
public:
	Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
	~Mesh();
	void Draw() const;
private:
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;

	GLuint m_indexCount;

	void Init(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
};