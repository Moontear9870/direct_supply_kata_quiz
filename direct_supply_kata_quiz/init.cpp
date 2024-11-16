#pragma once
#include "init.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void initSDL(void)
{
	int rendererFlags, windowFlags;
	rendererFlags = SDL_RENDERER_ACCELERATED;
	std::string windowName = "Direct Supply KATA Quiz";
	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Couldn't initialize SDL: %s\n" << SDL_GetError();
		exit(1);
	}

	app->window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if (!app->window) {
		std::cout << "Failed to open window: " << SDL_GetError();
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app->renderer = SDL_CreateRenderer(app->window, -1, rendererFlags);

	if (!app->renderer) {
		std::cout << "Failed to create renderer: " << SDL_GetError();
		exit(1);
	}
}