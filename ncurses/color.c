/**
 * Text color sample
 */

#include <stdio.h>
#include <ncurses.h>

int main() {
	initscr();
	start_color();
	use_default_colors();
	noecho();
	cbreak();

	init_pair(1, COLOR_BLUE, -1);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_RED);
	init_pair(4, COLOR_GREEN, -1);

	attron(COLOR_PAIR(1));
	clear();
	attroff(COLOR_PAIR(1));

	for (int i=1; i<=4; i++) {
		attron(COLOR_PAIR(i));
		mvaddstr(i, 3, "Hello, press key...");
		attroff(COLOR_PAIR(i));
	}

	getch();

	endwin();
	return 0;
}

