#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "Player.h"
#include "Window.h"

struct Camera
{
	Camera();
	~Camera() { }

	glm::mat4 GetProjMatrix() { return _proj_matrix; }
	glm::mat4 GetViewMatrix() { return _view_matrix; }

	int GetWindowWidth() { return _window_width; }
	int GetWindowHeight() { return _window_height; }

	void Update(Player* player, Window* window);


private:

	glm::vec3 _camera_pos;
	glm::vec3 _camera_front;
	glm::vec3 _camera_up;

	glm::mat4 _view_matrix;
	glm::mat4 _proj_matrix;

	int _window_width;
	int _window_height;
};