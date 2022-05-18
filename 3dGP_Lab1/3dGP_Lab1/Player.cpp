#include "Player.h"


Player::Player()
{
	_left = false;
	_right = false;
	_dead = false;
}

void Player::Update(std::vector<Box*> boxes)
{
	//moves player if needed
	if (_left == true)
	{
		if (GetPositionX() >= -10.0f)
		{
			UpdatePosition(glm::vec3(-0.1f, 0.0f, 0.0f));
		}
	}
	if (_right == true)
	{
		if (GetPositionX() <= 10.0f)
		{
			UpdatePosition(glm::vec3(0.1f, 0.0f, 0.0f));
		}
	}
	//checks if player collides with any boxes
	for (int i = 0; i < boxes.size(); i++)
	{
		if (boxCollision(boxes[i]) == true)
		{
			std::cout << "HIT" << std::endl;
			_dead = true;
			return;
		}
	}
}

bool Player::boxCollision(Box* box)
{
	glm::vec3 boxPos = box->GetPosition();
	glm::vec3 playerPos = GetPosition();
	//gets min and max of player and box collision area
	glm::vec3 minBoxPos = boxPos - glm::vec3(1.1f, 2.0f, 1.1f);
	glm::vec3 maxBoxPos = boxPos + glm::vec3(1.1f, 2.0f, 1.1f);

	glm::vec3 minPlayerPos = playerPos - glm::vec3(1.1f, 2.0f, 1.1f);
	glm::vec3 maxPlayerPos = playerPos + glm::vec3(1.1f, 2.0f, 1.1f);
	//checks if any points are touching
	return (minBoxPos.x <= maxPlayerPos.x && maxBoxPos.x >= minPlayerPos.x) &&
		(minBoxPos.y <= maxPlayerPos.y && maxBoxPos.y >= minPlayerPos.y) &&
		(minBoxPos.z <= maxPlayerPos.z && maxBoxPos.z >= minPlayerPos.z);
}