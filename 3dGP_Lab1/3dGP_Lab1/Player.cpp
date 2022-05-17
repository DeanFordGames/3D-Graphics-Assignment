#include "Player.h"


void Player::Update(std::vector<Box*> boxes)
{
	if (_left == true)
	{
		if (GetPositionX() >= -5.0f)
		{
			UpdatePosition(glm::vec3(-0.1f, 0.0f, 0.0f));
		}
	}
	if (_right == true)
	{
		if (GetPositionX() <= 5.0f)
		{
			UpdatePosition(glm::vec3(0.1f, 0.0f, 0.0f));
		}
	}

	for (int i = 0; i < boxes.size(); i++)
	{
		if (boxCollision(boxes[i]) == true)
		{
			std::cout << "HIT" << std::endl;
			return;
		}
	}
}

bool Player::boxCollision(Box* box)
{
	glm::vec3 boxPos = box->GetPosition();
	glm::vec3 playerPos = GetPosition();

	glm::vec3 minBoxPos = boxPos - glm::vec3(1.1f, 2.0f, 1.1f);
	glm::vec3 maxBoxPos = boxPos + glm::vec3(1.1f, 2.0f, 1.1f);

	glm::vec3 minPlayerPos = playerPos - glm::vec3(1.1f, 2.0f, 1.1f);
	glm::vec3 maxPlayerPos = playerPos + glm::vec3(1.1f, 2.0f, 1.1f);

	return (minBoxPos.x <= maxPlayerPos.x && maxBoxPos.x >= minPlayerPos.x) &&
		(minBoxPos.y <= maxPlayerPos.y && maxBoxPos.y >= minPlayerPos.y) &&
		(minBoxPos.z <= maxPlayerPos.z && maxBoxPos.z >= minPlayerPos.z);
}