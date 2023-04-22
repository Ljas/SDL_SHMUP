#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.h"
//#include "Game.h"
#include <iostream>
#include <fstream>


class Player {
    public:
        Player();
        Player(SDL_Renderer* ren);
        ~Player();
        Player(SDL_Renderer* &ren, Vector2d pos);

        Vector2d getPosition();
        Vector2d getVelocity();
        bool getFireStatus();
        bool Update();
        void Render();
        void HandleInput();
        void TakeHit(int damage);
    private:
    SDL_Renderer* renderer;
    SDL_Texture* tex;
    Vector2d position;
    Vector2d velocity;
    bool isDestroyed = 0;
    const double PLAYERSPEED = 2;
    double playerSpeed = PLAYERSPEED;
    bool fire = 0;
    int power = 10;
};