#pragma once

#include <SDL2/SDL.h>

struct Window
{
	Window();
	~Window();

	void Swap();

	void GetWindowSize(int &width, int &hieght) { SDL_GetWindowSize(window, &width, &hieght); }

private:

	SDL_Window *window;
};
