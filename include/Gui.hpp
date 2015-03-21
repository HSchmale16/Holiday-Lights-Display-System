/* Functions to control ncurses based GUI
 * @author Henry Schmale
 * @date January 11, 2015
 */

#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED

#include "../Defaults.hpp"
#include "HolidayLights.hpp"
#include <string>
#include <ncurses.h>
#include <cdk.h>

namespace gui {
// --- Functions ---
//!< Initializes the gui namespace
void init();

//!< shutsdown the gui namespace
void endGui();

//!< Initializes the gui for the show
void initShowGui();

//!< update the show gui
void updateShowGui(ServerData sd);

// Ends the Show gui
void endShowGui();

// Global Variables
extern CDKSCREEN *m_cdkscreen;	//!< Required for use of cdk
extern bool m_bGuiInited;
}

#endif // GUI_HPP_INCLUDED
