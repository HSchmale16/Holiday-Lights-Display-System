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
	WINDOW *screen;

	/* Initialize the Cdk screen.   */
	screen = initscr();
	cdkscreen = initCDKScreen (screen);

	/* Start CDK Colors */
	initCDKColor();
}

void gui::endGui()
{
	destroyCDKScreen (cdkscreen);
	endCDK();
}
