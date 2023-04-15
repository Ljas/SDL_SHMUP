all:
	g++ -I C:\devel\SDL2-32\include -L C:\devel\SDL2-32\lib -o main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image