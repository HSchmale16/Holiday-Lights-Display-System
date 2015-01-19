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
	time_t start, now;
	time(&start);
	time(&now);
	do
	{
		time(&now);
		// Run the gui
		// Activate the song when enough time has passed
		gui::updateShowGui(hl::currSongDat);
		sf::sleep(sf::milliseconds(UPDATE_T_PERIOD));
	}
	while(difftime(now, start) < SERVER_RUNS_FOR_SEC);
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
