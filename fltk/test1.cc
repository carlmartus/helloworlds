#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

static void callback(Fl_Widget *w, void *data) {
	printf("Hide!\n");

	Fl_Window *win = (Fl_Window*) data;
	win->hide();
}

int main(int argc, char **argv) {
	Fl_Window *window = new Fl_Window(300, 160, "Hello Window");

	Fl_Button *btn = new Fl_Button(20, 20, 260, 120, "Hello, World!");
	btn->callback(callback, window);

	window->end();
	window->show(argc, argv);

	return Fl::run();
}


