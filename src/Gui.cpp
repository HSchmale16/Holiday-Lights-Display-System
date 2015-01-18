/* Functions to control ncurses based GUI
 * @author Henry Schmale
 * @date January 11, 2015
 */

#include "../include/Gui.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string.h>

// External Variables
extern std::string NOW_PLAYING;

// Declare Namespace Globals to work with extern.
CDKSCREEN *gui::m_cdkscreen;
bool gui::m_bGuiInited = false;

void gui::init()
{
	if(!gui::m_bGuiInited)
	{
		// init ncurses
		WINDOW *screen;

		// Initialize the Cdk screen.
		screen = initscr();
		m_cdkscreen = initCDKScreen (screen);

		// Start CDK Colors
		initCDKColor();

		// Set inited
		gui::m_bGuiInited = true;
	}
}

void gui::endGui()
{
	if(gui::m_bGuiInited)
	{
		destroyCDKScreen (m_cdkscreen);
		endCDK();
		gui::m_bGuiInited = false;
	}
}

static CDKLABEL *showState;
static const char *currentShow[1];
void gui::initShowGui()
{
	if(!gui::m_bGuiInited)
	{
		gui::init();
	}
	currentShow[0] = NOW_PLAYING.c_str();
	showState = newCDKLabel(m_cdkscreen, CENTER, CENTER,
							currentShow, 1, true, true);
	if(!showState)
	{
		std::cout << "Failed to create current show label" << std::endl;
		exit(1);
	}
	drawCDKLabel(showState, true);
}

void gui::updateShowGui()
{
	if(showState)
	{
		currentShow[0] = NOW_PLAYING.c_str();
		setCDKLabel(showState, currentShow, 1, true);
	}
	else
	{
		std::cout << "show label is NULL: Can't use a null CDK Widget"
				  << std::endl;
		exit(1);
	}
	drawCDKLabel(showState, false);
}

void gui::endShowGui()
{
	destroyCDKLabel(showState);
	if(gui::m_bGuiInited)
	{
		gui::endGui();
	}
}
