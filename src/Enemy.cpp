#include "Enemy.h"
#include "EntityManager.h"
#include <cmath>

Enemy::Enemy() {}
Enemy::Enemy(SDL_Renderer* ren) {}

Enemy::~Enemy() {
    //std::cout << "poof" << " " << position.x << " " << position.y << std::endl;
    SDL_DestroyTexture(tex);
}

Enemy::Enemy(SDL_Renderer* &ren, Vector2d pos) {
    renderer = ren;

    position.x = pos.x;
    position.y = pos.y;

    tex = IMG_LoadTexture(renderer, "assets/enemy.png");
    if(tex == NULL) {
        std::cout << "Problem! " << IMG_GetError() << std::endl;
    }
}


bool Enemy::Update() {
    if((position.x > PLAYFIELD_RIGHT + 64 | position.y > PLAYFIELD_BOTTOM + 64 | position.x < PLAYFIELD_LEFT - 64 | position.y < PLAYFIELD_TOP - 64)) {
        isDestroyed = true;
    }

    position.x += velocity.x * enemySpeed;
    position.y += velocity.y * enemySpeed;

    double newTime = Utils::hireTimeInSeconds();
    double frameTime = newTime - currentTime;
    currentTime = newTime;
    accumulator += frameTime;
	if(accumulator >= fireDelta) {
		
		fire = true;
		accumulator -= fireDelta;
		
	} else fire = false;

    


    return isDestroyed;
}

void Enemy::Render() {

    SDL_Rect src;
    SDL_Rect dst;

    src.x = 0;
    src.y = 0;
    src.w = 23;
    src.h = 27;

    dst.x = position.x - 12;
    dst.y = position.y - 14;
    dst.w = 23;
    dst.h = 27;

    SDL_RenderCopy(renderer, tex, &src, &dst);
    //std::cout << "render call" << std::endl;
}

int Enemy::getFireStatus() {
    return fire;
}

Vector2d Enemy::getPosition() {
    return position;
}

Vector2d Enemy::getVelocity() {
    return velocity;
}

void Enemy::setDestroyed() {
    isDestroyed = true;
}

void Enemy::takeHit(int dmg) {
    HP -= dmg;
    if (HP < 1) setDestroyed();
}