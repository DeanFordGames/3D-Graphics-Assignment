#pragma once

#include "GameObject.h"
#include "Box.h"

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>


struct Player : public GameObject
{
	Player();
	~Player() {}

	void Update(std::vector<Box*> boxes);

	void SetLeft(bool left) { _left = left; }
	void SetRight(bool right) { _right = right; }

	bool GetDead() { return _dead; }


private:

	bool _left;
	bool _right;

	bool boxCollision(Box* box);

	bool _dead;

};