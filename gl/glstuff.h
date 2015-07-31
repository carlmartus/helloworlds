#pragma once
#include <GL/glew.h>

GLuint load_shaders_files(const char *vertFile, const char *fragFile);
GLuint load_shaders_text(const char *vertText, const char *fragText);
void gl_errors(void);
void wait_quit(void);


