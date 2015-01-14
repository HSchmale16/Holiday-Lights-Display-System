/* pgm entry point
 * @author Henry Schmale
 * @date January 11, 2015
 */

#include <iostream>
#include <ctime>
#include <SFML/System.hpp>
#include "include/HolidayLights.hpp"
#include "include/Admin.hpp"
#include "include/Gui.hpp"
#include "Defaults.hpp"

// Global Variables
int SERVER_RUNS_FOR_SEC; // server runs for this many seconds
std::string NOW_PLAYING; // What song is now playing

// Event Loop Types
int EventLoopLim();		// Limited run time
int EventLoopULim();	// Perpetual

int main(int argc, char** argv)
{
	// check if the args passed from terminal were bad or if the args were
	// auto-exit
	if(admin::parseArgs(argc, argv))
	{
		return 0; // if so quit
	}
	// start up
	gui::init();
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
	gui::endGui();
	hl::shutdown();
	return rc;
}

int EventLoopLim()
{
	time_t start, now;
	time(&start);
	time(&now);
	do
	{
		gui::updateGui();
		sf::sleep(sf::milliseconds(UPDATE_T_PERIOD));
	}
	while(difftime(now, start) < SERVER_RUNS_FOR_SEC);
	return 0;
}

int EventLoopULim()
{
	while(true)
	{
		gui::updateGui();
		sf::sleep(sf::milliseconds(UPDATE_T_PERIOD));
	}
	return 0;
}
