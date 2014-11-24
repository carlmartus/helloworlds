#include "glstuff.h"
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <sys/stat.h>
#include <assert.h>
#include <SDL/SDL.h>

static GLuint load_shader(const char *desc,
		const char *file_name, GLenum type);

GLuint load_shaders(const char *vert, const char *frag) {
	GLuint vert_id = load_shader("vert", vert, GL_VERTEX_SHADER);
	GLuint frag_id = load_shader("frag", frag, GL_FRAGMENT_SHADER);

	GLuint program = glCreateProgram();
	glAttachShader(program, vert_id);
	glAttachShader(program, frag_id);
	glLinkProgram(program);

	GLint result = GL_FALSE;
	int log_len;

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
	char *prog_err = alloca(log_len + 1);
	glGetProgramInfoLog(program, log_len, NULL, prog_err);
	printf("Linking:\n%s\n", prog_err);

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

static GLuint load_shader(
		const char *desc, const char *file_name, GLenum type) {
	GLuint sh = glCreateShader(type);

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

	// Compiling source
	glShaderSource(sh, 1, (const char**) &buf , NULL);
	glCompileShader(sh);

	// Checking errors
	GLint result = GL_FALSE;
	int log_len;
	glGetShaderiv(sh, GL_COMPILE_STATUS, &result);
	glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &log_len);

	char *log = alloca(log_len + 1);
	glGetShaderInfoLog(sh, log_len, NULL, log);

	printf("%s:\n%s\n", desc, log);

	return sh;
}

