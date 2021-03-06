#include <stdio.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include "glstuff.h"

int glstuff_main(float time) {
	static const float vertices[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
	};

	GLuint prog = load_shaders_files(
			"triangle_vert.glsl",
			"triangle_frag.glsl", NULL);
	glUseProgram(prog);

	GLuint vb;
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
			vertices, GL_STATIC_DRAW);

	set_attribute_count(1);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	return 0;
}

