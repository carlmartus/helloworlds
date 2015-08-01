#include <stdio.h>
#include <math.h>
#include "glstuff.h"

static const char *glslVert = GLSL_SOURCE(
	attribute vec2 in_loc;
	uniform float un_x, un_y;

	void main() {
		vec2 loc = vec2(
			in_loc.x + un_x,
			in_loc.y + un_y);
		gl_Position = vec4(loc, 0, 1);
	}
);

static const char *glslFrag = GLSL_SOURCE(
	void main() {
		gl_FragColor = vec4(1, 1, 0, 1);
	}
);

int glstuff_main(float time) {
	static int start = 0;
	static GLuint program, vbo;

	if (!start++) {
		program = load_shaders_text(glslVert, glslFrag,
				(const char*[]) { "in_loc", NULL });

		static const struct {
			float x, y;
		} data[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 0.0f, 1.0f },
		};
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
		gl_errors();
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint unifX = glGetUniformLocation(program, "un_x");
	GLuint unifY = glGetUniformLocation(program, "un_y");
	glUseProgram(program);

	glUniform1f(unifX, cosf(time));
	glUniform1f(unifY, sinf(time));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	gl_errors();

	return 1;
}

