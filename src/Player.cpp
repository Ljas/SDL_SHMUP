#include "Player.h"
#include "EntityManager.h"
#include <cmath>

Player::Player() {}
Player::Player(SDL_Renderer* ren) {}

Player::~Player() {
}

Player::Player(SDL_Renderer* &ren, Vector2d pos) {
    renderer = ren;

    position.x = pos.x;
    position.y = pos.y;

    tex = IMG_LoadTexture(renderer, "assets/ship.png");
    if(tex == NULL) {
        std::cout << "Problem! " << IMG_GetError() << std::endl;
    }
}

void Player::HandleInput() {
    const Uint8* keystates = SDL_GetKeyboardState(NULL); 

	playerSpeed = PLAYERSPEED;
	velocity.x = 0;
	velocity.y = 0;

	if (keystates[SDL_SCANCODE_UP]) {
			velocity.y = -1;
		}

		if (keystates[SDL_SCANCODE_LEFT]) {
			velocity.x = -1;
		}

		if (keystates[SDL_SCANCODE_DOWN]) {
			velocity.y = 1;
		}

		if (keystates[SDL_SCANCODE_RIGHT]) {
			velocity.x = 1;
		}
		
		if (keystates[SDL_SCANCODE_LSHIFT]) {
			playerSpeed = PLAYERSPEED / 2;
		}

        if (keystates[SDL_SCANCODE_Z]) {
			fire = true;
		} else fire = false;
}

bool Player::Update() {
    if (velocity.x != 0 && velocity.y != 0) {
        velocity.x *= 0.7071;
        velocity.y *= 0.7071;
    }

    if(position.x < PLAYFIELD_LEFT && velocity.x < 0) velocity.x = 0;
    if(position.y < PLAYFIELD_TOP && velocity.y < 0) velocity.y = 0;
    
    if(position.x > (PLAYFIELD_RIGHT) - 26 && velocity.x > 0) velocity.x = 0;
    if(position.y > (PLAYFIELD_BOTTOM) - 32 && velocity.y > 0) velocity.y = 0;

    position.x += velocity.x * playerSpeed;
    position.y += velocity.y * playerSpeed;


    return isDestroyed;
}

void Player::Render() {

    SDL_Rect src;
    SDL_Rect dst;

    src.x = 0;
    src.y = 0;
    src.w = 26;
    src.h = 32;

    dst.x = position.x;
    dst.y = position.y;
    dst.w = 26;
    dst.h = 32;

    SDL_RenderCopy(renderer, tex, &src, &dst);
}

bool Player::getFireStatus() {
    return fire;
}

Vector2d Player::getPosition() {
    return position;
}

Vector2d Player::getVelocity() {
    return velocity;
}