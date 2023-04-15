#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* ren) {
}
Bullet::~Bullet() {}
Bullet::Bullet(SDL_Renderer* ren, Vector2d pos, Vector2d vel)
: position(pos), velocity(vel) {
}

Vector2d Bullet::getPosition() {
    return position;
}

Vector2d Bullet::getVelocity() {
    return velocity;
}
