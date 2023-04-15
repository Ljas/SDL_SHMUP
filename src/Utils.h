#pragma once
#include <SDL2/SDL.h>

namespace Utils
{
	inline double hireTimeInSeconds()
	{
		double t = SDL_GetTicks64();
		t *= 0.001;

		return t;
	}
}