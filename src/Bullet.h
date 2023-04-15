#pragma once
#include <SDL2/SDL.h>
#include "Math.h"
#include "Game.h"

class Bullet {
    public:
        Bullet(SDL_Renderer* ren);
        ~Bullet();
        Bullet(SDL_Renderer* ren, Vector2d pos, Vector2d vel);

        Vector2d getPosition();
        Vector2d getVelocity();
    private:
    SDL_Renderer* renderer;
    SDL_Texture* tex;
    Vector2d position;
    Vector2d velocity;
};