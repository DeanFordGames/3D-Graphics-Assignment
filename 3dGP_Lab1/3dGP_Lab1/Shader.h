#include <GL/glew.h>
#include <string>

struct Shader
{
	Shader(const std::string& _vertSrc, const std::string& _fragSrc);
	~Shader();

	void use();
	GLuint getId();

private:
	GLuint m_progId;
};