#include <stdio.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include "glstuff.h"

int
main()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(640, 480, 0, SDL_OPENGL);

	glewInit();

	glClearColor(0.3, 0.4, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint va;
	glGenVertexArrays(1, &va);
	glBindVertexArray(va);

	static const float vertices[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
	};

	GLuint prog = load_shaders(
			"triangle_vert.glsl",
			"triangle_frag.glsl");
	glUseProgram(prog);

	GLuint vb;
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
			vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	SDL_GL_SwapBuffers();
	SDL_Delay(800);

	SDL_Quit();
	return 0;
}

