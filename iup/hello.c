#include <stdio.h>
#include <stdlib.h>
#include <iup/iup.h>

static int
exit_cb(void)
{
	return IUP_CLOSE;
}

int
main(int argc, char *argv[])
{
	// declare widgets
	Ihandle *btn, *lbl, *vb, *dlg;

	// initialize iup
	IupOpen(&argc, &argv);

	// create widgets and set their attributes
	btn=IupButton("&Ok", "");
	IupSetCallback(btn,"ACTION", (Icallback) exit_cb);
	IupSetAttribute(btn, "EXPAND", "Yes");
	IupSetAttribute(btn, "TIP", "Exit button");

	lbl=IupLabel("Hello,world!");

	vb=IupVbox(lbl, btn, NULL);
	IupSetAttribute(vb, "GAP", "10");
	IupSetAttribute(vb, "MARGIN", "10x10");
	IupSetAttribute(vb, "ALIGNMENT", "ACENTER");

	dlg=IupDialog(vb);
	IupSetAttribute(dlg, "TITLE", "Hello");

	// Map widgets and show dialog
	IupShow(dlg);

	// Wait for user interaction
	IupMainLoop();

	// Clean up
	IupDestroy(dlg);
	IupClose();
	return EXIT_SUCCESS;
}

