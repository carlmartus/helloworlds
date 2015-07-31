#include <stdio.h>
#include <SDL/SDL.h>
#include "glstuff.h"

#define GLSL_SOURCE(msg) "#version 100\n" #msg

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

void glstuff_main() {
	GLuint program = load_shaders_text(glslVert, glslFrag,
			(const char*[]) { "in_loc", NULL });
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

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	gl_errors();
}

