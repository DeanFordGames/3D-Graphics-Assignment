#include "Player.h"


void Player::Update()
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
}