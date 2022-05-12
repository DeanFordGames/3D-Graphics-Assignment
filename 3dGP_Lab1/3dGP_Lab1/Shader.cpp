#include "Shader.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <stdexcept>
#include <vector>
#include <iostream>
#include <fstream>

std::string load_file(const std::string& _path)
{
	std::ifstream file(_path.c_str());
	if (!file.is_open())
	{
		throw std::runtime_error("failed to open file");
	}
	std::string rtn;
	std::string line;

	while (!file.eof())
	{
		std::getline(file, line);
		rtn += line + '\n';
	}
	return rtn;
}

Shader::Shader(const std::string& _vertPath, const std::string& _fragPath)
{
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

	std::string contents = load_file(_vertPath);
	const char *src = contents.c_str();
	glShaderSource(vertexShaderId, 1, &src, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::runtime_error("vertex shader didnt do the success");
	}



	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	contents = load_file(_fragPath);
	src = contents.c_str();
	glShaderSource(fragmentShaderId, 1, &src, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH,
			&maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(fragmentShaderId, maxLength,
			&maxLength, &errorLog[0]);
		std::cout << &errorLog.at(0) << std::endl;
		throw std::runtime_error("fragment shader didnt do the success");
	}

	m_progId = glCreateProgram();
	glAttachShader(m_progId, vertexShaderId);
	glAttachShader(m_progId, fragmentShaderId);
	glBindAttribLocation(m_progId, 0, "a_Position");
	glBindAttribLocation(m_progId, 1, "a_TexCoord");
	glBindAttribLocation(m_progId, 2, "a_Normal");
	glLinkProgram(m_progId);
	success = 0;
	glGetProgramiv(m_progId, GL_LINK_STATUS, &success);
	if (!success)
	{
		throw std::runtime_error("couldnt link program");
	}

	glDetachShader(m_progId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(m_progId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

void Shader::use()
{
	glUseProgram(m_progId);
}

GLuint Shader::getId()
{
	return m_progId;
}

Shader::~Shader()
{
}
