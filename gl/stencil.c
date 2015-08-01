#include <stdio.h>
#include <math.h>
#include "glstuff.h"

typedef struct {
	float x, y;
} Vertex0;

static const char *glslVert0 = GLSL_SOURCE(
	attribute vec2 in_loc;

	void main() {
		gl_Position = vec4(in_loc, 0, 1);
	}
);

static const char *glslFrag0 = GLSL_SOURCE(
	void main() {
		gl_FragColor = vec4(0, 1, 0, 1);
	}
);

typedef struct {
	float x, y;
	int radius;
} Vertex1;

static const char *glslVert1 = GLSL_SOURCE(
	attribute vec2 in_loc;
	attribute float in_rad;
	uniform float un_x, un_y;

	void main() {
		gl_Position = vec4(
			in_loc.x + un_x,
			in_loc.y + un_y,
			0, 1);
		gl_PointSize = in_rad;
	}
);

static const char *glslFrag1 = GLSL_SOURCE(
	void main() {
		lowp vec2 coord = 2.0*gl_PointCoord - 1.0;
		if (length(coord) > 1.0) discard;
		gl_FragColor = vec4(0, 0, 0, 1);
	}
);

int glstuff_main(float time) {
	static int start = 0;
	static GLuint program0, vab0;
	static GLuint program1, vab1, uniform1x, uniform1y;

	if (!start++) {
		glEnable(GL_STENCIL_TEST);

		// Program 0
		program0 = load_shaders_text(glslVert0, glslFrag0, NULL);

		Vertex0 vd0[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 0.0f, 1.0f },
		};

		glGenBuffers(1, &vab0);
		glBindBuffer(GL_ARRAY_BUFFER, vab0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vd0), vd0, GL_STATIC_DRAW);
		gl_errors();

		// Program 1
		program1 = load_shaders_text(glslVert1, glslFrag1,
				(const char*[]) { "in_loc", "in_rad" });
		uniform1x = glGetUniformLocation(program1, "un_x");
		uniform1y = glGetUniformLocation(program1, "un_y");

		Vertex1 vd1[] = {
			{ 0.0f, 0.0f, 30 },
			{ 0.5f, 0.0f, 60 },
			{ 0.0f, 0.5f, 90 },
		};

		glGenBuffers(1, &vab1);
		glBindBuffer(GL_ARRAY_BUFFER, vab1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vd1), &vd1, GL_STATIC_DRAW);
	}

    glStencilMask(0xff); // Enable mask to clear
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Draw stencil
    glStencilMask(0xff);
	glStencilFunc(GL_ALWAYS, 1, 0xff);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);

	glUseProgram(program1);
	glBindBuffer(GL_ARRAY_BUFFER, vab1);
	set_attribute_count(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex1), NULL);
	glVertexAttribPointer(1, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(Vertex1), (void*) 8);

	glUniform1f(uniform1x, 0.1f + 0.2f*cosf(time));
	glUniform1f(uniform1y, 0.1f + 0.2f*sinf(time));

	glDrawArrays(GL_POINTS, 0, 3);
	gl_errors();

	// Draw stuff for stencil = 1
    glStencilMask(0);
	glStencilFunc(GL_EQUAL, 1, 0xff);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);

	glUseProgram(program0);
	glBindBuffer(GL_ARRAY_BUFFER, vab0);
	set_attribute_count(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	gl_errors();

	return 1;
}

