#include "glstuff.h"
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <sys/stat.h>
#include <assert.h>
#include <SDL/SDL.h>

static GLuint compile_shader(const char *text, const char *desc, GLenum type);
static GLuint link_program(GLuint vert, GLuint frag, const char **attributes);
static GLuint load_shader(const char *desc,
		const char *file_name, GLenum type);

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(640, 480, 0, SDL_OPENGL);

	glewInit();
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);
	gl_errors();

	glClearColor(0.3, 0.4, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	extern void glstuff_main();
	glstuff_main();

	SDL_GL_SwapBuffers();
	wait_quit();

	SDL_Quit();
	return 0;
}

GLuint load_shaders_files(const char *vertFile, const char *fragFile, const char **attributes) {
	GLuint vert_id = load_shader("vert file", vertFile, GL_VERTEX_SHADER);
	GLuint frag_id = load_shader("frag file", fragFile, GL_FRAGMENT_SHADER);

	GLuint program = link_program(vert_id, frag_id, attributes);

	glDeleteShader(vert_id);
	glDeleteShader(frag_id);

	return program;
}

GLuint load_shaders_text(const char *vertText, const char *fragText, const char **attributes) {
	GLuint vert_id = compile_shader(vertText, "vert text", GL_VERTEX_SHADER);
	GLuint frag_id = compile_shader(fragText, "frag text", GL_FRAGMENT_SHADER);

	GLuint program = link_program(vert_id, frag_id, attributes);

	glDeleteShader(vert_id);
	glDeleteShader(frag_id);

	return program;
}

void gl_errors(void) {
	assert(glGetError() == GL_NO_ERROR);
}

void wait_quit(void) {
	while (1) {
		SDL_Event event;
		SDL_WaitEvent(&event);

		switch (event.type) {
			case SDL_KEYDOWN :
			case SDL_QUIT :
				return;
			default : break;
		}
	}
}

static GLuint compile_shader(const char *text, const char *desc, GLenum type) {
	GLuint sh = glCreateShader(type);
	glShaderSource(sh, 1, (const char**) &text , NULL);
	glCompileShader(sh);

	// Checking errors
	GLint result = GL_FALSE;
	int log_len;
	glGetShaderiv(sh, GL_COMPILE_STATUS, &result);
	glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &log_len);

	char *log = alloca(log_len + 1);
	glGetShaderInfoLog(sh, log_len, NULL, log);

	if (result != GL_TRUE) {
		printf("%s:\n%s\n", desc, log);
	}

	return sh;
}

static GLuint link_program(GLuint vert, GLuint frag, const char **attributes) {
	GLuint program = glCreateProgram();
	glAttachShader(program, vert);
	glAttachShader(program, frag);

	if (attributes) {
		unsigned i = 0;
		while (*attributes != NULL) {
			glBindAttribLocation(program, i, *attributes);
			gl_errors();
			i++;
			attributes++;
		}
	}

	glLinkProgram(program);

	GLint result = GL_FALSE;
	int log_len;

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
	char *prog_err = alloca(log_len + 1);
	glGetProgramInfoLog(program, log_len, NULL, prog_err);
	if (result != GL_TRUE) {
		printf("Linking:\n%s\n", prog_err);
	}

	return program;
}

static GLuint load_shader(
		const char *desc, const char *file_name, GLenum type) {

	// Loading source
	struct stat st;
	if (stat(file_name, &st) != 0) {
		printf("File doesn't exist: %s\n", file_name);
		exit(1);
	}
	char *buf = alloca(st.st_size + 1);
	FILE *fd = fopen(file_name, "r");
	fread(buf, st.st_size, 1, fd);
	fclose(fd);
	buf[st.st_size] = '\0';

	return compile_shader(buf, desc, type);
}

