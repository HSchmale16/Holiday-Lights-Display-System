/* Functions to control ncurses based GUI
 * @author Henry Schmale
 * @date January 11, 2015
 */

#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED

#include <ncurses.h>
#include <string>

namespace gui
{
	// --- Functions ---
	// Initializes the gui
	void init();

	// Update the gui shown during shows
	void updateShowGui();

	// shutsdown the gui
	void endGui();

	// prints in the middle of the screen
	void printInMiddle(WINDOW *win, int starty, int startx, int width,
					   std::string str);

	// --- CONSTANTS ---
	const int SCR_WDTH = 80; // Width of the terminal
	const int SCR_HGHT = 25; // Height of the terminal
}

#endif // GUI_HPP_INCLUDED
