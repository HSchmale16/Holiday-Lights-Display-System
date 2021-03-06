/**@file main.cpp
 * @author Henry Schmale
 * @date January 11, 2015
 * \mainpage Holiday Lights Display Server
 * A system to dynamically generate a light show to some music then stream
 * some shows to a couple of embedded computers over TCP.
 */

#include <iostream>
#include <ctime>
#include <SFML/System.hpp>
#include <glog/logging.h>
#include "include/HolidayLights.hpp"
#include "include/Admin.hpp"
#include "include/Gui.hpp"
#include "Defaults.hpp"
#include "version.h"

// Global Variables
int SERVER_RUNS_FOR_SEC; // server runs for this many seconds
bool SHOW_EDIT_MODE_ON = false;	// is the prog in show edit mode
ServerData serverstate;

// Event Loop Types
int EventLoopLim();		// Limited run time
int EventLoopULim();	// Perpetual

int main(int argc, char** argv) {
    // init logging
    FLAGS_log_dir = "./logs/";
    google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "Initialized Google Logging";
    // Log the build revision of this program
    LOG(INFO) << "Program Version is "
              << AutoVersion::FULLVERSION_STRING;
    LOG(INFO) << "Program has been built "
              << AutoVersion::BUILDS_COUNT << " times";
#ifdef BUILD_DEBUG
    LOG(INFO) << "This is the DEBUG build of the program";
#endif // BUILD_DEBUG
#ifdef BUILD_RELEASE
    LOG(INFO) << "This is the RELEASE build of the program";
#endif // BUILD_RELEASE
#ifdef BUILD_PROFILE
    LOG(INFO) << "This is the PROFILING build of the program";
#endif // BUILD_PROFILE
    // check if the args passed from terminal were bad or if the args were
    // auto-exit
    if(admin::parseArgs(argc, argv)) {
        LOG(INFO) << "Quiting because the args passed said to do so";
        return 0; // if so quit
    }
    // start up
    hl::initLights();
    gui::initShowGui();

    // Launch the event loop
    int rc;
    if(SERVER_RUNS_FOR_SEC == 0) {
        rc = EventLoopULim();
    } else {
        rc = EventLoopLim();
    }

    // Shutdown
    gui::endShowGui();
    hl::shutdown();
    std::cout << double(clock()) / CLOCKS_PER_SEC << std::endl;
    return rc;
}

int EventLoopLim() {
    int waitPeriod = hl::startShow();
    time_t serverStartTime, now, songStartedTime;
    time(&songStartedTime);
    time(&serverStartTime);
    time(&now);
    // init struct
    serverstate.m_serverStarted = serverStartTime;
    serverstate.m_songStarted = songStartedTime;
    serverstate.m_waitPeriod = waitPeriod;
    serverstate.m_currSong = hl::currSongDat.m_name;
    // event loop
    do {
        time(&now);
        // update server state
        serverstate.m_now = now;
        // Run the gui
        // Activate the song when enough time has passed
        if(waitPeriod < difftime(now, songStartedTime)) {
            if((waitPeriod + INTERMISSION) < difftime(now, songStartedTime)) {
                waitPeriod = hl::startShow();
                time(&songStartedTime);
                serverstate.m_songStarted = songStartedTime;
                serverstate.m_waitPeriod = waitPeriod;
                serverstate.m_currSong = hl::currSongDat.m_name;
            } else if(
                (waitPeriod + INTERMISSION) > difftime(now, songStartedTime)) {
                serverstate.m_currSong = "THIS IS AN INTERMISSION";
            }
        }
        gui::updateShowGui(serverstate);
        sf::sleep(sf::milliseconds(UPDATE_T_PERIOD));
    } while(difftime(now, serverStartTime) < SERVER_RUNS_FOR_SEC);
    return 0;
}

int EventLoopULim() {
    while(true) {
        // Run the gui
        // Activate the song when enough time has passed
        sf::sleep(sf::milliseconds(UPDATE_T_PERIOD));
    }
    return 0;
}

void emergencyShutdown(int rc) {
    LOG(FATAL) << "Something bad happened causing an emergency shutdown";
    gui::endShowGui();
    hl::shutdown();
    exit(rc);
}
