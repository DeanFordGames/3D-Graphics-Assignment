#pragma once

#include "GameObject.h"

#include <SDL2/SDL.h>


struct Player : public GameObject
{
	Player() {}
	~Player() {}

	void Update();

	void SetLeft(bool left) { _left = left; }
	void SetRight(bool right) { _right = right; }

private:

	bool _left;
	bool _right;

};