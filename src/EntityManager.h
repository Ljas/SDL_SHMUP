#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.h"
#include <vector>
#include "Bullet.h"
#include <stdlib.h>
#include <list>
//Bullet[] bulletArray;


class EntityManager {
    public:
        EntityManager();
        EntityManager(SDL_Renderer *&ren);
        ~EntityManager();

        int CreateTestBullet();
        void Update();
        void Render();
    private:
        SDL_Renderer* renderer;
        std::list<Bullet> bullets;
        int bulletIndex = 0;
        
};