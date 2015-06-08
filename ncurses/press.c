#include <stdio.h>
#include <ncurses.h>

int main() {
	initscr();
	noecho();
	cbreak();

	clear();

	mvaddstr(2, 3, "Hello, press key...");

	getch();

	endwin();
	return 0;
}

