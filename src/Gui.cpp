/* Functions to control ncurses based GUI
 * @author Henry Schmale
 * @date January 11, 2015
 */

#include "../include/Gui.hpp"
#include "../version.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string.h>
#include <vector>
#include <glog/logging.h>

// decl externs
extern std::vector<hl::ClientDevice> clients;

union ConversionUnion
{
    long long numericValue;
    char byteValues[sizeof(long long)];
};

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

        // init ncurses color
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);

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

const char *generateVisualizer(char c[8])
{
    static char ch[65];
    ch[64] = '\0';
    int index = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if((c[i] & BIT_FLAGS[j]) == BIT_FLAGS[j])
            {
                ch[index] = '@';
            }
            else
            {
                ch[index] = '_';
            }
            index++;
        }
    }
    return ch;
}

void gui::updateShowGui(ServerData sd)
{
    clear();
    // title
    mvprintw(0, (COLS - sd.m_currSong.length()) / 2, sd.m_currSong.c_str());
    // Song visualizer
    unsigned int tIndex =
        difftime(sd.m_now, sd.m_songStarted) * BYTES_PER_INSTRUCT * 10;
    ConversionUnion myCU;
    if(tIndex < sd.m_currShow.length())
    {
        strncpy(myCU.byteValues, // this is a dirty hack
                sd.m_currShow.substr(tIndex,
                                     tIndex + BYTES_PER_INSTRUCT).c_str(),
                sizeof(long long));
    }
    mvprintw(LINES / 2, (COLS - 64)/2,
             generateVisualizer(myCU.byteValues));

    // Status messages bottom left corner
    mvprintw(LINES - 3, 0, "%d Clients Connected", clients.size());
    mvprintw(LINES - 2, 0, "dT Index: %d of %d",
             int(difftime(sd.m_now, sd.m_songStarted)) * 10,
             sd.m_waitPeriod);
    mvprintw(LINES - 1, 0, "Server Has Been Running: %d Seconds",
             int(difftime(sd.m_now, sd.m_serverStarted)));
    /// Build Version - Bottom Right Hand Corner
    mvprintw(LINES - 1,
             COLS - (strlen(AutoVersion::FULLVERSION_STRING) + 10),
             "Version: %s", AutoVersion::FULLVERSION_STRING);
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
