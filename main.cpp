/* pgm entry point
 * @author Henry Schmale
 * @date January 11, 2015
 */

#include <iostream>
#include <ctime>
#include <SFML/System.hpp>
#include <glog/logging.h>
#include "include/HolidayLights.hpp"
#include "include/Admin.hpp"
#include "include/Gui.hpp"
#include "Defaults.hpp"

// Global Variables
int SERVER_RUNS_FOR_SEC; // server runs for this many seconds
bool SHOW_EDIT_MODE_ON = false;	// is the prog in show edit mode

// Event Loop Types
int EventLoopLim();		// Limited run time
int EventLoopULim();	// Perpetual

int main(int argc, char** argv)
{
    // init logging
    FLAGS_log_dir = "./logs/";
    google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "Initialized Google Logging";
    // check if the args passed from terminal were bad or if the args were
    // auto-exit
    if(admin::parseArgs(argc, argv))
    {
        LOG(INFO) << "Quiting because the args passed said to do so";
        return 0; // if so quit
    }
    // start up
    gui::initShowGui();
    hl::initLights();
    hl::startShow();
    // Launch the event loop
    int rc;
    if(SERVER_RUNS_FOR_SEC == 0)
    {
        rc = EventLoopULim();
    }
    else
    {
        rc = EventLoopLim();
    }

    // Shutdown
    gui::endShowGui();
    hl::shutdown();
    std::cout << double(clock()) / CLOCKS_PER_SEC << std::endl;
    return rc;
}

int EventLoopLim()
{
    ServerData mySd;
    int waitPeriod = 0;
    time_t serverStartTime, now, songStartedTime;
    time(&songStartedTime);
    time(&serverStartTime);
    time(&now);
    // init struct
    mySd.m_serverStarted = serverStartTime;
    mySd.m_songStarted = songStartedTime;
    mySd.m_waitPeriod = waitPeriod;
    mySd.m_currSong = hl::currSongDat.m_name;
    // event loop
    do
    {
        time(&now);
        // update server state
        mySd.m_now = now;
        // Run the gui
        // Activate the song when enough time has passed
        if(waitPeriod < difftime(now, songStartedTime))
        {
            if((waitPeriod + INTERMISSION) < difftime(now, songStartedTime))
            {
                waitPeriod = hl::startShow();
                time(&songStartedTime);
                mySd.m_songStarted = songStartedTime;
                mySd.m_waitPeriod = waitPeriod;
                mySd.m_currSong = hl::currSongDat.m_name;
            }
            else
            {
                mySd.m_currSong = "THIS IS AN INTERMISSION";
            }
        }
        gui::updateShowGui(mySd);
        sf::sleep(sf::milliseconds(UPDATE_T_PERIOD));
    }
    while(difftime(now, serverStartTime) < SERVER_RUNS_FOR_SEC);
    return 0;
}

int EventLoopULim()
{
    while(true)
    {
        // Run the gui
        // Activate the song when enough time has passed
        sf::sleep(sf::milliseconds(UPDATE_T_PERIOD));
    }
    return 0;
}

void emergencyShutdown(int rc)
{
	LOG(FATAL) << "Something bad happened causing an emergency shutdown";
    gui::endShowGui();
    hl::shutdown();
    exit(rc);
}
