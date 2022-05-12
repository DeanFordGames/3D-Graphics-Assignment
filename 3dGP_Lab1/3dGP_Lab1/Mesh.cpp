#include "Mesh.h"

#include <stdexcept>

const GLfloat positions[] = {
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
};

const GLfloat texCoords[] = {
	0.0f,0.0f,
	0.0f,1.0f,
	1.0f,1.0f,
	1.0f,1.0f,
	1.0f,0.0f,
	0.0f,0.0f
};

Mesh::Mesh(int type)
{
	glGenBuffers(1, &m_posVboId);

	if (!m_posVboId)
	{
		throw std::runtime_error("position buffer is no");
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_posVboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &m_vaoId);

	if (!m_vaoId)
	{
		throw std::runtime_error("VAO id thing not work");
	}

	glBindVertexArray(m_vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, m_posVboId);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


	glGenBuffers(1, &m_coordVboId);

	if (!m_coordVboId)
	{
		throw std::runtime_error("color buffer ID failed");
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_coordVboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_coordVboId);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLuint Mesh::getId()
{
	return m_vaoId;
}

int Mesh::vert_Count()
{
	return 6;
}
