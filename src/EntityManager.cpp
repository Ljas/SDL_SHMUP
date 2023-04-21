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

void EntityManager::CreateTestEnemy() {
    
    SDL_Rect src;
    SDL_Rect dst;
    int x = PLAYFIELD_LEFT + rand() % PLAYFIELD_RIGHT;
    //std::cout << x << std::endl;
    enemies.emplace_back(renderer, Vector2d(x,0));
    //std::cout << enemies.size() << std::endl;    
    //delete bullet;
}

void EntityManager::CreateTestShot() {
    //std::cout << "Hello?" << std::endl;
    SDL_Rect src;
    SDL_Rect dst;
    int x = player->getPosition().x;
    int y = player->getPosition().y;
    double velX = 0;
    double velY = -400 + (player->getVelocity().y * 50);
    //std::cout << velX << " " << velY << std::endl;
    playerShots.emplace_back(renderer, Vector2d(x-13,y-6), Vector2d(velX,velY),"assets/shot.png", 16);
    playerShots.emplace_back(renderer, Vector2d(x+13,y-6), Vector2d(velX,velY),"assets/shot.png", 16);
    //std::cout << playerShots.size() << std::endl;     
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

    //once more with collision
    iter = bullets.begin();
    end  = bullets.end();

    while (iter != end)
    {
        PlayerCollision(*iter);
        ++iter;
    };

    //enemy management
    std::list< Enemy >::iterator iterE = enemies.begin();
    std::list< Enemy >::iterator endE  = enemies.end();

    while (iterE != endE)
    {
        endE = enemies.end();

        if (iterE->Update() == true)
        {
            iterE = enemies.erase(iterE);
            ++iterE;
        }
        else/**/
        {
            
            if (iterE->getFireStatus() == true) {
                //std::cout << "here" << std::endl;
                double velX = player->getPosition().x - iterE->getPosition().x;
                double velY = player->getPosition().y - iterE->getPosition().y;

                double hypo = std::hypot(std::abs(velX), std::abs(velY));
                //std::cout << hypo << std::endl;
                hypo /= 150;
                velX /= hypo;
                velY /= hypo;
              
                bullets.emplace_back(renderer, Vector2d(iterE->getPosition().x,iterE->getPosition().y), Vector2d(velX,velY), "assets/basicBullet.png", 16);
            }
            ++iterE;
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

    EnemyCollision();
}

void EntityManager::Render() {
    player->Render();

    std::list< Enemy >::iterator iterE = enemies.begin();
    std::list< Enemy >::iterator endE  = enemies.end();

    while (iterE != endE)
    {
        iterE->Render();
        ++iterE;
    }

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

void EntityManager::PlayerCollision(Bullet &bullet) {
    double bCenterX = bullet.getPosition().x;
    double bCenterY = bullet.getPosition().y;

    // player is 26x32 for now, and radius 5
    double pCenterX = player->getPosition().x;
    double pCenterY = player->getPosition().y - 4;

    double xDist = std::abs(bCenterX - pCenterX);
    double yDist = std::abs(bCenterY - pCenterY);
    double distance = std::hypot(xDist, yDist);

    if (distance < (bullet.getRadius() + 6)) {
        bullet.setDestroyed();
        //std::cout << player->getPosition().x << " " << player->getPosition().y << " || " << bCenterX << " " << bCenterY << " || " << distance << std::endl;
    }
}

void EntityManager::EnemyCollision() {
    
    std::list< Enemy >::iterator iterE = enemies.begin();
    std::list< Enemy >::iterator endE  = enemies.end();
    std::list< Bullet >::iterator iter = playerShots.begin();
    std::list< Bullet >::iterator end  = playerShots.end();
    int eRadius = 12;
    int bRadius;
    double eCenterX;
    double eCenterY;
    while (iterE != endE)
    {
        eCenterX = iterE->getPosition().x;
        eCenterY = iterE->getPosition().y;
        iter = playerShots.begin();
        end  = playerShots.end();

        while (iter != end) {
            bRadius = iter->getRadius();
            double bCenterX = iter->getPosition().x;
            double bCenterY = iter->getPosition().y;

            double xDist = std::abs(bCenterX - eCenterX);
            double yDist = std::abs(bCenterY - eCenterY);
            double distance = std::hypot(xDist, yDist);
            //std::cout << distance << " ";
            //std::cout << &iterE << " " << &endE << " || " << &iter << " " << &end << std::endl;
        if (distance < (bRadius + eRadius)) {
            
            iter->setDestroyed();
            iterE->takeHit();
            
        }
            
            //std::cout << "poof" << std::endl;
            ++iter;
        }
        
        ++iterE;
    }
}