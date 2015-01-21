/* Functions to control ncurses based GUI
 * @author Henry Schmale
 * @date January 11, 2015
 */

#include "../include/Gui.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string.h>
#include <vector>
#include <glog/logging.h>

// decl externs
extern std::vector<hl::ClientDevice> clients;

// Declare Namespace Globals to work with extern.
CDKSCREEN *gui::m_cdkscreen;	//!< CDK SCREEN Required for use of CDK
bool gui::m_bGuiInited = false;

void gui::init()
{
    if(!gui::m_bGuiInited)
    {
        LOG(INFO) << "Initializing ncurses and cdk";
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
        LOG(INFO) << "Calling the ncurses and cdk shutdown functions";
        destroyCDKScreen (m_cdkscreen);
        endCDK();
        gui::m_bGuiInited = false;
    }
}

void gui::initShowGui()
{
    LOG(INFO) << "Initializing GUI for show";
    if(!gui::m_bGuiInited)
    {
        gui::init();
    }

}

void gui::updateShowGui(ServerData sd)
{
    clear();
    mvprintw(0, (COLS - sd.m_currSong.length()) / 2, sd.m_currSong.c_str());
    mvprintw(21, 0, "%d Clients Connected", clients.size());
    mvprintw(22, 0, "dT Index: %d of %d",
             int(difftime(sd.m_now, sd.m_songStarted)),
             sd.m_waitPeriod);
    mvprintw(23, 0, "Server Has Been Running: %d Seconds",
             int(difftime(sd.m_now, sd.m_serverStarted)));
    refresh();
}

void gui::endShowGui()
{
    if(gui::m_bGuiInited)
    {
        LOG(INFO) << "Ending Show mode GUI";
        gui::endGui();
    }
}
