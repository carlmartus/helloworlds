#include <stdio.h>
#include <SDL/SDL.h>

int main(int argc, char **argv) {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_SetVideoMode(640, 480, 0, SDL_SWSURFACE);

	for (int i=0; i<100; i++) {
	}

	SDL_Quit();
	return 0;
}

