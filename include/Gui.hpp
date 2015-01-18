/* Functions to control ncurses based GUI
 * @author Henry Schmale
 * @date January 11, 2015
 */

#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED

#include <string>
#include <ncurses.h>
#include <cdk.h>

namespace gui
{
	// --- Functions ---
	// Initializes the gui
	void init();

	// shutsdown the gui
	void endGui();

	// Global Variables
	extern CDKSCREEN *cdkscreen;
}

#endif // GUI_HPP_INCLUDED
