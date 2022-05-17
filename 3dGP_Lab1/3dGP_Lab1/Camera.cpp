#include "Camera.h"

Camera::Camera()
{
	_camera_pos = glm::vec3(0.0f, 3.0f, 1.0f);
	_camera_front = glm::vec3(0.0f, -0.3f, -1.0f);
	_camera_up = glm::vec3(0.0f, 1.0f, 0.0f);

	_proj_matrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 200.0f);
	_view_matrix = glm::lookAt(_camera_pos, _camera_pos + _camera_front, _camera_up);
}

void Camera::Update(Player* player)
{
	_camera_pos.x = player->GetPositionX();

	_view_matrix = glm::lookAt(_camera_pos, _camera_pos + _camera_front, _camera_up);
}
