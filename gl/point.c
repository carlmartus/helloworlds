#include <GL/glew.h>
#include <SDL/SDL.h>
#include "glstuff.h"

typedef struct {
	float x, y;
	float size;
} Vertice;

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(640, 480, 0, SDL_OPENGL);

	glewInit();
	glEnable(GL_PROGRAM_POINT_SIZE);
	gl_errors();

	GLuint prog = load_shaders(
			"point_vert.glsl",
			"point_frag.glsl");
	glUseProgram(prog);

	static const Vertice data[] = {
		{ 0.0f, 0.0f, 150.0f },
		{ 0.1f, 0.2f, 20.0f },
		{-0.3f,-0.8f, 8.0f },
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
			sizeof(data), data, GL_STATIC_DRAW);
	gl_errors();

	glClearColor(0.3, 0.4, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	gl_errors();

	glDrawArrays(GL_POINTS, 0, sizeof(data)/sizeof(data[0]));
	gl_errors();

	SDL_GL_SwapBuffers();
	wait_quit();

	SDL_Quit();

	return 0;
}

