#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/ext.hpp>

#include "Player.h"

struct Camera
{
	Camera();
	~Camera() { }

	glm::mat4 GetProjMatrix() { return _proj_matrix; }
	glm::mat4 GetViewMatrix() { return _view_matrix; }

	void Update(Player* player);


private:

	glm::vec3 _camera_pos;
	glm::vec3 _camera_front;
	glm::vec3 _camera_up;

	glm::mat4 _view_matrix;
	glm::mat4 _proj_matrix;
};