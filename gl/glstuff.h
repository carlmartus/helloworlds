#pragma once
#include <GL/glew.h>

GLuint load_shaders_files(const char *vertFile, const char *fragFile, const char **attributes);
GLuint load_shaders_text(const char *vertText, const char *fragText, const char **attributes);
void gl_errors(void);
void wait_quit(void);


