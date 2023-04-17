#include "Bullet.h"

Bullet::Bullet() {}
Bullet::Bullet(SDL_Renderer* ren) {
}
Bullet::~Bullet() {
    //std::cout << "poof @ " << position.x << " " << position.y << std::endl;
    SDL_DestroyTexture(tex);
}
Bullet::Bullet(SDL_Renderer *&ren, Vector2d pos, Vector2d vel)
: renderer(ren), position(pos), velocity(vel) {

    
    tex = IMG_LoadTexture(renderer, "assets/basicBullet.png");
    if(tex == NULL) {
        std::cout << "TexFail " << SDL_GetError() << std::endl;
    }
}

Vector2d Bullet::getPosition() {
    return position;
}

Vector2d Bullet::getVelocity() {
    return velocity;
}

bool Bullet::Update() {
    if((position.x > 800 | position.y > 600 | position.x < -100 | position.y < -100)) {
        isDestroyed = true;
    }
    else isDestroyed = false;

    position.x += velocity.x / 100;
    position.y += velocity.y / 100;


    return isDestroyed;
}

void Bullet::Render() {
    SDL_Rect src;
    SDL_Rect dst;

    src.x = 0;
    src.y = 0;
    src.w = 16;
    src.h = 16;

    dst.x = position.x;
    dst.y = position.y;
    dst.w = 8;
    dst.h = 8;

    SDL_RenderCopy(renderer, tex, &src, &dst);
}