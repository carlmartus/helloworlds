#include <stdio.h>
#include <stdlib.h>
#include <iup/iup.h>
#include <iup/iupgl.h>
#include <GL/gl.h>

int
redraw(Ihandle *self, float x, float y)
{
	char *size = IupGetAttribute(self, "RASTERSIZE");
	int w, h;
	sscanf(size, "%dx%d", &w, &h);

	IupGLMakeCurrent(self);

	glViewport(0, 0, w, h);
	glClearColor(1.0, 1.0, 1.0, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES); 
	glColor4ub(0xff, 0, 0, 0xff);
	glVertex2i(-1, -1);
	glColor4ub(0, 0xff, 0, 0xff);
	glVertex2i(1, -1);
	glColor4ub(0, 0, 0xff, 0xff);
	glVertex2i(-1, 1);
	glEnd();

	IupGLSwapBuffers(self); 

	printf("Render %d %d\n", w, h);

	return IUP_DEFAULT;
}

int
main(int argc, char **argv)
{
	// Start IUP
	IupOpen(&argc, &argv);

	// Start IUP GL
	IupGLCanvasOpen();

	// Create GL Canvas
	Ihandle *canvas = IupGLCanvas(NULL);
	IupSetCallback(canvas, "ACTION", (Icallback) redraw);
	IupSetAttribute(canvas, IUP_BUFFER, IUP_DOUBLE);
	IupSetAttribute(canvas, "RASTERSIZE", "123x200");
	IupSetAttribute(canvas, "EXPAND", "YES");

	Ihandle *win = IupDialog(canvas);
	IupSetAttribute(win, "TITLE", "IUP OpenGL");
	IupSetAttribute(win, "SIZE", "400x400");

	IupShow(win);
	IupMainLoop();
	IupClose();

	return EXIT_SUCCESS;
}

