#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "Math.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int x, int y, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();
	void handleInput();

	//static SDL_Renderer* renderer;

	bool running()
	{
		return isRunning;
	};
private:
	bool isRunning = 0;
	SDL_Window* window;
};