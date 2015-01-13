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
	// Initializes the gui
	void init();

	void updateGui();

	// shutsdown the gui
	void endGui();

	// prints in the middle of the screen
	void printInMiddle(WINDOW *win, int starty, int startx, int width,
					   std::string str);
}

#endif // GUI_HPP_INCLUDED
