#include <stdio.h>
#include <GL/glew.h>
#include <SDL/SDL.h>

int
main()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(640, 480, 0, SDL_OPENGL);

	glewInit();

	SDL_Quit();
	return 0;
}

