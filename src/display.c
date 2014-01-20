//
// display.c
//

#include <ctype.h>
#include <stdarg.h>
#include "world.h"
#include "display.h"

#define NONE (-1)

static int max_width;
static int max_height;
static int last_col = NONE;

WINDOW * memoscr;
WINDOW * dispscr;
WINDOW * statscr;

void init_disp(void)
{
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, max_height, max_width);

	// just hide the cursor for now
	curs_set(0);

	memoscr = newwin(1, max_width, 0, 0);
	dispscr = newwin(max_height - 4, max_width, 1, 0);
	statscr = newwin(3, max_width, max_height - 3, 0);
}

void end_disp(void)
{
	endwin();
}

void reset_memos(void)
{
	wmove(memoscr, 0, 0);
	wclrtoeol(memoscr);
	last_col = NONE;
}

void memo(const char * fmt, ...)
{
	int dummy __attribute__((unused));;
	va_list vl;
	va_start(vl, fmt);

	if (last_col != NONE) {
		mvwprintw(memoscr, 0, last_col, "...");
		wgetch(memoscr);
	}

	wmove(memoscr, 0, 0);
	wclrtoeol(memoscr);
	vw_printw(memoscr, fmt, vl);
	getyx(memoscr, dummy, last_col);
	wrefresh(memoscr);

	va_end(vl);
}

void statline(int ln, const char * fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);

	wmove(statscr, ln, 0);
	wclrtoeol(statscr);
	vw_printw(statscr, fmt, vl);
	wrefresh(statscr);

	va_end(vl);
}
