#pragma once

#include "GameObject.h"
#include "Player.h"

struct Box: public GameObject
{
	Box() {}
	~Box() {}

	void Update(Player* player);

private:


};