#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.h"
//#include "Game.h"
#include <iostream>
#include <fstream>

class Bullet {
    public:
        Bullet();
        Bullet(SDL_Renderer* ren);
        ~Bullet();
        Bullet(SDL_Renderer* &ren, Vector2d pos, Vector2d vel);
        Bullet(SDL_Renderer* &ren, Vector2d pos, Vector2d vel, const char text[], int size);

        Vector2d getPosition();
        Vector2d getVelocity();
        void setDestroyed();
        double getRadius();
        bool Update();
        void Render();
        int getDamage();
    private:
    SDL_Renderer* renderer;
    SDL_Texture* tex;
    Vector2d position;
    Vector2d velocity;
    bool isDestroyed = 0;
    int bulletSize = 16;
    int damage = 10;
};