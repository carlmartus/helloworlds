#pragma once
#include <GL/glew.h>

GLuint load_shaders(const char *vert, const char *frag);
void gl_errors(void);
void wait_quit(void);


