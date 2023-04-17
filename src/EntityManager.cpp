#include "EntityManager.h"

EntityManager::EntityManager() {};
EntityManager::~EntityManager() {};
EntityManager::EntityManager(SDL_Renderer* &ren)
: renderer(ren) {

};

int EntityManager::CreateTestBullet() {
    
    SDL_Rect src;
    SDL_Rect dst;
    int x = rand() % 800;
    double velX = rand() % 100 - 50;
    double velY = rand() % 100 + 50;
    //std::cout << velX << " " << velY << std::endl;
    bullets.emplace_back(renderer, Vector2d(x,0), Vector2d(velX,velY));
    //std::cout << bullets.size() << std::endl;    
    //delete bullet;
    return 0;
}

void EntityManager::Update() {
    std::list< Bullet >::iterator iter = bullets.begin();
    std::list< Bullet >::iterator end  = bullets.end();

    while (iter != end)
    {
    std::list< Bullet >::iterator end  = bullets.end();

    if (iter->Update() == true)
    {
        iter = bullets.erase(iter);
        ++iter;
    }
    else/**/
    {
        // BTW, who is deleting pItem, a.k.a. (*iter)?
        ++iter;
    }
    }


}

void EntityManager::Render() {
    std::list< Bullet >::iterator iter = bullets.begin();
    std::list< Bullet >::iterator end  = bullets.end();

    while (iter != end)
    {
        iter->Render();
        ++iter;
    }
    
}