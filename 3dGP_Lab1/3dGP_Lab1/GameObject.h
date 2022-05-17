#pragma once

#include <glm/glm.hpp>
#include <stdexcept>


struct GameObject
{
	GameObject();
	~GameObject() {}

	void SetPosition(glm::vec3 pos) { _position = pos; }
	void UpdatePosition(glm::vec3 pos) { _position += pos; }
	glm::vec3 GetPosition() { return _position; }

	float GetPositionZ() { return _position.z; }
	float GetPositionX() { return _position.x; }
	float GetPositionY() { return _position.y; }

private:

	glm::vec3 _position;

};