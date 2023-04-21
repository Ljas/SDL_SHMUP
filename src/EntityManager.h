#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.h"
#include <vector>
#include "Bullet.h"
#include <stdlib.h>
#include <list>
#include "Player.h"
#include "Utils.h"
#include "Enemy.h"
#include <cmath>
//Bullet[] bulletArray;


class EntityManager {
    public:
        EntityManager();
        EntityManager(SDL_Renderer *&ren);
        ~EntityManager();

        int CreateTestBullet();
        void CreateTestShot();
        void InitPlayer();
        void Update();
        void Render();
        void PlayerCollision(Bullet &bullet);
        void CreateTestEnemy();
        void EnemyCollision();
    private:
        SDL_Renderer* renderer;
        std::list<Bullet> bullets;
        std::list<Bullet> playerShots;
        std::list<Enemy> enemies;
        int bulletIndex = 0;
        Player* player;
        
};