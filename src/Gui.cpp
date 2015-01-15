/* Functions to control ncurses based GUI
 * @author Henry Schmale
 * @date January 11, 2015
 */

#include "../include/Gui.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>

// External Variables
extern std::string NOW_PLAYING;

void gui::init()
{
	// init ncurses
	initscr();
	keypad(stdscr, true);
	noecho();
	cbreak();
	curs_set(0);	// make text cursor invisible
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
}

void gui::updateShowGui()
{
	clear();
	gui::printInMiddle(NULL, 0, 0, 0, "Holiday Lighs System Server");
	gui::printInMiddle(NULL, 3, 0, 0, "Now Playing:");
	gui::printInMiddle(NULL, 4, 0, 0, NOW_PLAYING);
	refresh();
}

void gui::endGui()
{
	endwin();
}

void gui::printInMiddle(WINDOW *win, int starty, int startx, int width,
						std::string str)
{
	int length, x, y;
	float temp;

	if(win == NULL)
	{
		win = stdscr;
	}
	getyx(win, y, x);
	if(startx != 0)
	{
		x = startx;
	}
	if(starty != 0)
	{
		y = starty;
	}
	if(width == 0)
	{
		width = 80;
	}

	length = str.length();
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	mvwprintw(win, y, x, "%s", str.c_str());
}
