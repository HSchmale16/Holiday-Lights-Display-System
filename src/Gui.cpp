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

static char screen[gui::SCR_HGHT][gui::SCR_WDTH];

void gui::init()
{
	// zero the file global screen
	for(int i = 0; i < gui::SCR_HGHT; i++)
		for(int j = 0; j < gui::SCR_WDTH; j++)
			screen[i][j] = ' ';

	// init ncurses
	initscr();
	keypad(stdscr, true);
	noecho();
	cbreak();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
}

void gui::printChrAt(int y, int x, char c)
{
    screen[y][x] = c;
}

void gui::updateShowGui()
{
	clear();
	gui::printInMiddle(NULL, 0, 0, 0, "Holiday Lighs System Server");
	gui::printInMiddle(NULL, 3, 0, 0, "Now Playing:");
	gui::printInMiddle(NULL, 4, 0, 0, NOW_PLAYING);
	refresh();
}

void gui::updateGeneralGui()
{
	clear();
	for(int i = 0; i < SCR_HGHT; i++)
	{
		for(int j = 0; j < gui::SCR_WDTH; j++)
		{
            printw(&screen[i][j]);
		}
	}
	refresh();
}

void gui::endGui()
{
	endwin();
	for(int i = 0; i < gui::SCR_HGHT; i++)
		for(int j = 0; j < gui::SCR_WDTH; j++)
			std::cout << screen[i][j];
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
