#include <GL/glew.h>

struct Mesh
{
	Mesh(int type);
	GLuint getId();
	int vert_Count();

private:
	GLuint m_vaoId;
	GLuint m_posVboId;
	GLuint m_coordVboId;
};
