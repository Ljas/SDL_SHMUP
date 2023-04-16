#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.h"
#include <vector>
#include "Bullet.h"

class EntityManager {
    public:
        EntityManager();
        EntityManager(SDL_Renderer* ren);
        ~EntityManager();

        int EntityManager::CreateBullet(Vector2d pos, Vector2d vel);
    private:
        SDL_Renderer* renderer;
        std::vector<Bullet> bullets;
};