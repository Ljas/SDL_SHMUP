#include "EntityManager.h"
const double TIMESTEP = 0.08;
double shotCountdown = 0.0;
double currentDelta = Utils::hireTimeInSeconds();


EntityManager::EntityManager() {};
EntityManager::~EntityManager() {
    delete player;
};
EntityManager::EntityManager(SDL_Renderer* &ren)
: renderer(ren) {

};

int EntityManager::CreateTestBullet() {
    
    SDL_Rect src;
    SDL_Rect dst;
    int x = PLAYFIELD_LEFT + rand() % PLAYFIELD_RIGHT;
    double velX = rand() % 100 - 50;
    double velY = rand() % 100 + 50;
    //std::cout << velX << " " << velY << std::endl;
    bullets.emplace_back(renderer, Vector2d(x,0), Vector2d(velX,velY), "assets/basicBullet.png", 16);
    //std::cout << bullets.size() << std::endl;    
    //delete bullet;
    return 0;
}

void EntityManager::CreateTestShot() {
    //std::cout << "Hello?" << std::endl;
    SDL_Rect src;
    SDL_Rect dst;
    int x = player->getPosition().x;
    int y = player->getPosition().y;
    double velX = 0;
    double velY = -250 + (player->getVelocity().y * 50);
    //std::cout << velX << " " << velY << std::endl;
    playerShots.emplace_back(renderer, Vector2d(x+5,y+16), Vector2d(velX,velY),"assets/shot.png", 16);
    playerShots.emplace_back(renderer, Vector2d(x+29,y+16), Vector2d(velX,velY),"assets/shot.png", 16);
    std::cout << playerShots.size() << std::endl;     
    //delete bullet;
}

void EntityManager::InitPlayer() {
    player = new Player(renderer, Vector2d((PLAYFIELD_RIGHT - PLAYFIELD_LEFT) / 2, (PLAYFIELD_BOTTOM - 128)));
    //std::cout << "Player initialized" << std::endl;
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

    //Temporary repeat with testshots
    iter = playerShots.begin();
    end  = playerShots.end();

    while (iter != end)
    {
    end  = playerShots.end();

    if (iter->Update() == true)
    {
        iter = playerShots.erase(iter);
        ++iter;
    }
    else/**/
    {
        // BTW, who is deleting pItem, a.k.a. (*iter)?
        ++iter;
    }
    }

    double newTime = Utils::hireTimeInSeconds();
        double frameTime = newTime - currentDelta;
        currentDelta = newTime;
        shotCountdown += frameTime;
	if(shotCountdown >= TIMESTEP) {
		
		if(player->getFireStatus()) {
        //std::cout << "fire" << std::endl;
        CreateTestShot();
    }
		
		shotCountdown -= TIMESTEP;
		
	}

    player->HandleInput();
    
    player->Update();
}

void EntityManager::Render() {
    player->Render();

    std::list< Bullet >::iterator iter = bullets.begin();
    std::list< Bullet >::iterator end  = bullets.end();

    while (iter != end)
    {
        iter->Render();
        ++iter;
    }

    iter = playerShots.begin();
    end  = playerShots.end();

    while (iter != end)
    {
        iter->Render();
        ++iter;
    }
    
}