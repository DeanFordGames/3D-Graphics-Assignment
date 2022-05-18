#include "Camera.h"

Camera::Camera()
{
	//position and rotation vectors for camera
	_camera_pos = glm::vec3(0.0f, 3.0f, 1.0f);
	_camera_front = glm::vec3(0.0f, -0.3f, -1.0f);
	_camera_up = glm::vec3(0.0f, 1.0f, 0.0f);

	//first initalization of window size
	_window_width = 800.0f;
	_window_height = 600.0f;

	//applying eveything to matrices
	_proj_matrix = glm::perspective(glm::radians(45.0f), (float)_window_width / (float)_window_height, 0.1f, 200.0f);
	_view_matrix = glm::lookAt(_camera_pos, _camera_pos + _camera_front, _camera_up);
}

void Camera::Update(Player* player, Window* window)
{
	//gets camera to follow player
	_camera_pos.x = player->GetPositionX();

	//update matrices
	_view_matrix = glm::lookAt(_camera_pos, _camera_pos + _camera_front, _camera_up);

	window->GetWindowSize(_window_width, _window_height);
	_proj_matrix = glm::perspective(glm::radians(45.0f), (float)_window_width / (float)_window_height, 0.1f, 200.0f);
}
