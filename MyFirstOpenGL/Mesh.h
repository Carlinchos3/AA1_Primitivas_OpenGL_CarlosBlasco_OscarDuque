#pragma once
#include <GL/glew.h>
#include <vector>


class Mesh {
public:
	Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
	~Mesh();
	void Draw() const;
private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	GLuint indexCount;

	void Init(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
};