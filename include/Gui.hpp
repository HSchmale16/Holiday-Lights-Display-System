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

	/** \brief Update/Redraw the general purpose gui
	 * \return nothing
	 */
	void updateGeneralGui();

	/** \brief prints a character at a specific (y,x) coord in the editor gui
	 * matrix. When using the general purpose gui
	 *
	 * \param y - the y coord to print at.
	 * \param x - the x coord to print at.
	 * \param c - the character to print out
	 * \return nothing
	 * Updates a specific value in the @file src/Gui.cpp global screen at that
	 * spot in the matrix.
	 */
	void printChrAt(int y, int x, char c);

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
