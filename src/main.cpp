#include <iostream>
#include <SDL2/SDL.h>

#include "Game.h"
#include "Utils.h"

const int WIDTH = 800, HEIGHT = 600;
Game* game = nullptr;
//int a = 0;

int main(int argc, char *argv[]) {
    game = new Game();

    game->init("Game window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

    const double TIMESTEP = 0.01;
    double accumulator = 0.0;
    double currentTime = Utils::hireTimeInSeconds();

    while (game->running()) {
        double newTime = Utils::hireTimeInSeconds();
        double frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;
        
        while (accumulator >= TIMESTEP)
        {
            game->handleEvents();
            game->update();
            accumulator -= TIMESTEP;
        }
        game->render();

        //std::cout << a++ << std::endl;
    }

    game->clean();

    return EXIT_SUCCESS;
}