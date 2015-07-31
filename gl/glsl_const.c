#include <stdio.h>
#include <SDL/SDL.h>
#include "glstuff.h"

#define GLSL_PREFIX "#version 100\n"
#define GLSL_SOURCE(msg) GLSL_PREFIX #msg

static const char *glslVert = GLSL_SOURCE(
	attribute vec2 in_loc;

	void main() {
		gl_Position = vec4(in_loc, 0, 1);
	}
);

static const char *glslFrag = GLSL_SOURCE(
	void main() {
		gl_FragColor = vec4(1, 1, 0, 1);
	}
);

int main(int argc, char **argv) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(640, 480, 0, SDL_OPENGL);

	glewInit();

	GLuint program = load_shaders_text(glslVert, glslFrag);
	glUseProgram(program);

	static const struct {
		float x, y;
	} data[] = {
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 1.0f },
	};
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	gl_errors();

	glClearColor(0.3, 0.4, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	gl_errors();

	SDL_GL_SwapBuffers();
	wait_quit(); // Wait for key press

	SDL_Quit();
	return 0;
}

