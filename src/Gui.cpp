/* Functions to control ncurses based GUI
 * @author Henry Schmale
 * @date January 11, 2015
 */

#include "../include/Gui.hpp"
#include <cstdlib>
#include <cstring>

using namespace gui;

void gui::init()
{
	initscr();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
}

void gui::updateGui()
{
	clear();
	printInMiddle(NULL, 0, 0, 0, "Holiday Lighs System Server");
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
