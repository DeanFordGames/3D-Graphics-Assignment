#pragma once

#include <SDL2/SDL.h>

struct Window
{
	Window();
	~Window();

	void Swap();

private:

	SDL_Window *window;
};
