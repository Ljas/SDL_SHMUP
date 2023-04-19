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

Bullet::Bullet(SDL_Renderer *&ren, Vector2d pos, Vector2d vel, const char text[], int size)
: renderer(ren), position(pos), velocity(vel), bulletSize(size) {

    
    tex = IMG_LoadTexture(renderer, text);
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
    if((position.x > PLAYFIELD_RIGHT + 64 | position.y > PLAYFIELD_BOTTOM + 64 | position.x < PLAYFIELD_LEFT - 64 | position.y < PLAYFIELD_TOP - 64)) {
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
    src.w = bulletSize;
    src.h = bulletSize;

    dst.x = position.x - (bulletSize / 2);
    dst.y = position.y - (bulletSize / 2);
    dst.w = 8;
    dst.h = 8;

    SDL_RenderCopy(renderer, tex, &src, &dst);
}