#include "Game.h"
#include "Utils.h"

SDL_Renderer* renderer;

static int SCALE = 1;
SDL_Rect src;
SDL_Rect dst;
double playerX = 0;
double playerY = 0;
const int PLAYERSPEED = 4;
int playerSpeed = PLAYERSPEED;
EntityManager *manager;
const double TIMESTEP = 0.001;
    double accumulator = 0.0;
    double currentTime = Utils::hireTimeInSeconds();

Game::Game(){
	};

Game::~Game(){
};

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{

	int flags = 0;
	isRunning = true;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING > 0))
	{
		std::cout << "SDL initialization error: " << SDL_GetError() << std::endl;
		isRunning = false;
	}

	window = SDL_CreateWindow(title, x, y, width, height, flags);

	if (window == NULL)
	{
		std::cout << "Window init fail: " << SDL_GetError() << std::endl;
		isRunning = false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | flags);
	if (renderer == NULL)
	{
		std::cout << "Renderer failure: " << SDL_GetError() << std::endl;
		isRunning = false;
	}

    if(!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_Init initialization error: " << SDL_GetError() << std::endl;

    tex = IMG_LoadTexture(renderer, "assets/ship.png");
    if(tex == NULL) {
        std::cout << "Problem! " << IMG_GetError() << std::endl;
    }
	
	dst.x = 300;
	dst.y = 400;

	manager = new EntityManager(renderer);

	//SDL_EnableKeyRepeat(0,0);
};

SDL_Renderer* Game::getRenderer() {
	return renderer;
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
	handleInput();
};

void Game::handleInput() {
	const Uint8* keystates = SDL_GetKeyboardState(NULL); 

	playerSpeed = PLAYERSPEED;
	playerX = 0;
	playerY = 0;

	if (keystates[SDL_SCANCODE_UP]) {
			playerY = -1;
		}

		if (keystates[SDL_SCANCODE_LEFT]) {
			playerX = -1;
		}

		if (keystates[SDL_SCANCODE_DOWN]) {
			playerY = 1;
		}

		if (keystates[SDL_SCANCODE_RIGHT]) {
			playerX = 1;
		}
		
		if (keystates[SDL_SCANCODE_LSHIFT]) {
			playerSpeed = PLAYERSPEED / 2;
		}
}

void Game::update()
{

	double newTime = Utils::hireTimeInSeconds();
        double frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;
	if(accumulator >= TIMESTEP) {
		
		manager->CreateTestBullet();
		
		accumulator -= TIMESTEP;
		
	}
	manager->Update();	

};

void Game::render()
{
    
	SDL_RenderClear(renderer);
	//add stuff to render

    
	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;
	
	dst.x += playerX * playerSpeed;
	dst.y += playerY * playerSpeed;
	//std::cout << dst.x << " " << playerX << " " << dst.y << " " << playerY << " " << playerSpeed << std::endl;
	dst.w = 32 * SCALE;
	dst.h = 32 * SCALE;
    SDL_RenderCopy(renderer, tex, &src, &dst);
	manager->Render();
    

	SDL_RenderPresent(renderer);
};

void Game::clean()
{
	delete manager;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(tex);
	SDL_Quit();
	std::cout << "Quit successfully" << std::endl;
};