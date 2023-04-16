#include "EntityManager.h"

EntityManager::EntityManager() {};
EntityManager::~EntityManager() {};
EntityManager::EntityManager(SDL_Renderer* ren)
: renderer(ren) {

};

int EntityManager::CreateBullet(Vector2d pos, Vector2d vel) {
    
}