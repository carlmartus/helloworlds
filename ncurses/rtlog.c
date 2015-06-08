/**
 * Realtime logging
 * Multiple threads
 *
 * For greater applications you should use a mutex for curses operations
 */

#include <stdio.h>
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

static WINDOW *logWin, *cmdWin;
static int running;
static pthread_t thread;

static void *logThread();
static void killCmdWindow();
static void killAllWindows();
static void buildWindows();
static void rebuildWindows();

int main() {
	initscr();
	echo();
	cbreak();

	logWin = cmdWin = NULL;

	buildWindows();
	doupdate();

	running = 1;
	pthread_create(&thread, NULL, logThread, NULL);

	while (1) {
		char buf[500];
		int r = wgetnstr(cmdWin, buf, sizeof(buf));

		if (r == ERR) break;
		else if (r == KEY_RESIZE) rebuildWindows();
		else if (strlen(buf) == 0) break; // No text == exit

		// Rebuild command window
		killCmdWindow();
		buildWindows();

		// Post text
		waddstr(logWin, buf);
		waddstr(logWin, "\n");
		wrefresh(logWin);
		wrefresh(cmdWin);
	}

	running = 0;
	pthread_join(thread, NULL);

	killAllWindows();
	endwin();
	return 0;
}


static void *logThread() {
	do {
		waddstr(logWin, "Hello\n");
		wrefresh(logWin);
		wrefresh(cmdWin);
		sleep(1);
	} while (running);

	return NULL;
}

static void killCmdWindow() {
	delwin(cmdWin);
	cmdWin = NULL;
}

static void killAllWindows() {
	killCmdWindow();
}

static void buildWindows() {
	if (!logWin) {
		logWin = newwin(LINES-1, COLS, 1, 0);
		scrollok(logWin, TRUE);
	}

	if (!cmdWin) cmdWin = newwin(1, COLS, 0, 0);
}

static void rebuildWindows() {
	killAllWindows();
	buildWindows();
}


