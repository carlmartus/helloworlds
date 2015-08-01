#pragma once
#include <GL/glew.h>

#define GLSL_SOURCE(...) "#version 100\nprecision mediump float;" #__VA_ARGS__
#define GLSL_SIZE(obj) ((const GLvoid*) sizeof(obj))

GLuint load_shaders_files(const char *vertFile, const char *fragFile, const char **attributes);
GLuint load_shaders_text(const char *vertText, const char *fragText, const char **attributes);
void set_attribute_count(unsigned count);
void gl_errors(void);
void wait_quit(void);


