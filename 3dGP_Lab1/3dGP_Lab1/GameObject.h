#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/ext.hpp>

#include <stdexcept>

#include <wavefront/wavefront.h>

#include "Shader.h"

struct GameObject
{
	GameObject();
	~GameObject() {}

	void SetPosition(glm::vec3 pos) { _position = pos; }
	void UpdatePosition(glm::vec3 pos) { _position += pos; }
	glm::vec3 GetPosition() { return _position; }

	void SetAngle(float angle) { _angle = angle; }
	void UpdateAngle(float angle) { _angle += angle; }
	float GetAngle() { return _angle; }

	float GetPositionZ() { return _position.z; }
	float GetPositionX() { return _position.x; }
	float GetPositionY() { return _position.y; }

	WfModel GetModel() { return _model; }

	void SetModel(const char* filePath);

	void Draw(glm::mat4 projMatrix, glm::mat4 viewMatrix);

private:

	glm::vec3 _position;
	float _angle;

	WfModel _model;

	glm::mat4 _model_matrix;

	GLint _model_loc;
	GLint _view_loc;
	GLint _proj_loc;

	Shader* _shader;

};