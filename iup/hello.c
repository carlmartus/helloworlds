#include <stdio.h>
#include <stdlib.h>
#include <iup/iup.h>

static int
cb_print(void)
{
	printf("Hello World!\n");
	return 0;
}

static int
cb_exit(void)
{
	return IUP_CLOSE;
}

int
main(int argc, char *argv[])
{
	IupOpen(&argc, &argv);

	// Label
	Ihandle *lbl = IupLabel("Hello, world!");
	IupSetAttribute(lbl, "EXPAND", "YES");
	IupSetAttribute(lbl, "ALIGNMENT", "ACENTER");

	// Print button
	Ihandle *btn_print = IupButton("&Print stdout", "");
	IupSetCallback(btn_print,"ACTION", (Icallback) cb_print);
	IupSetAttribute(btn_print, "EXPAND", "HORIZONTAL");

	// Exit button
	Ihandle *btn_exit = IupButton("E&xit", "");
	IupSetCallback(btn_exit,"ACTION", (Icallback) cb_exit);
	IupSetAttribute(btn_exit, "EXPAND", "HORIZONTAL");

	// Container
	Ihandle *vb = IupVbox(lbl, btn_print, btn_exit, NULL);
	IupSetAttribute(vb, "GAP", "10");
	IupSetAttribute(vb, "MARGIN", "10x10");

	// Window
	Ihandle *dlg = IupDialog(vb);
	IupSetAttribute(dlg, "TITLE", "Hello");
	IupSetAttribute(dlg, "SIZE", "120x80");
	IupShow(dlg);

	// Start
	IupMainLoop();

	// Shut down
	IupDestroy(dlg);
	IupClose();

	return EXIT_SUCCESS;
}

