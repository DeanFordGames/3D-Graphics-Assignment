#include "Window.h"

#include <GL/glew.h>
#include <stdexcept>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Window::Window()
{//create and initalize window
	 window = SDL_CreateWindow("Game",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::runtime_error("Failed to create OpenGL context");
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initalize glew");
	}
}

Window::~Window()
{//clear stuff
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::Swap()
{//to swap for the next frame
	SDL_GL_SwapWindow(window);
}