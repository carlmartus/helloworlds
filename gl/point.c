#include <GL/glew.h>
#include <SDL/SDL.h>
#include "glstuff.h"

typedef struct {
	float x, y;
	float size;
} Vertice;

int glstuff_main(float time) {
	GLuint prog = load_shaders_files(
			"point_vert.glsl",
			"point_frag.glsl", NULL);
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

	set_attribute_count(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	gl_errors();

	glDrawArrays(GL_POINTS, 0, sizeof(data)/sizeof(data[0]));
	gl_errors();

	return 0;
}

