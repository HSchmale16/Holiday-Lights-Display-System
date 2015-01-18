/* Functions to control ncurses based GUI
 * @author Henry Schmale
 * @date January 11, 2015
 */

#include "../include/Gui.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string.h>

// Declare Namespace Globals to work with extern.
CDKSCREEN *gui::m_cdkscreen;
bool gui::m_bGuiInited = false;

void gui::init()
{
	if(!gui::m_bGuiInited)
	{
		initscr();
		m_cdkscreen = initCDKScreen (stdscr);

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

}

void gui::updateShowGui(hl::SongData sd)
{
	clear();
	mvprintw(0, (COLS - sd.m_name.length()) / 2, sd.m_name.c_str());
	refresh();
}

void gui::endShowGui()
{
	destroyCDKLabel(showState);
	if(gui::m_bGuiInited)
	{
		gui::endGui();
	}
}
