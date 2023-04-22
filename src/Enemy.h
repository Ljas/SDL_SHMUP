#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.h"
//#include "Game.h"
#include <iostream>
#include <fstream>
#include "Utils.h"


class Enemy {
    public:
        Enemy();
        Enemy(SDL_Renderer* ren);
        ~Enemy();
        Enemy(SDL_Renderer* &ren, Vector2d pos);

        Vector2d getPosition();
        Vector2d getVelocity();
        int getFireStatus();
        void setDestroyed();
        void takeHit(int damage);
        bool Update();
        void Render();
    private:
    SDL_Renderer* renderer;
    SDL_Texture* tex;
    Vector2d position;
    Vector2d velocity = Vector2d(0,1);
    bool isDestroyed = 0;
    const double PLAYERSPEED = 2;
    double enemySpeed = 1.0;
    bool fire = 0;
    double fireDelta = 0.8;
    double currentTime = Utils::hireTimeInSeconds();
    double accumulator = 0.0;
    const int radius = 12;
    int HP = 50;
};