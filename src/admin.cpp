/** Implemenation of functions defined in ../include/admin.hpp
 * @author Henry Schmale
 * @date January 11, 2015
 */

#include "../include/Admin.hpp"
#include "../Defaults.hpp"
#include "../include/HolidayLights.hpp" // for db commands
#include "../include/Gui.hpp"
#include "../include/Synthesis.hpp"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ncurses.h>

extern int SERVER_RUNS_FOR_SEC; // how long the server should run for

int admin::parseArgs(int argc, char** argv)
{
	if(argc <= 1)
	{
		admin::args::noArgs();
		return 1;
	}
	std::vector<std::string> args = admin::args::createArgVector(argc, argv);
	for(unsigned int i = 0;  i < args.size(); i++)
	{
		for(unsigned int j = 0; j < admin::args::NUM_POSSIBLE_ARGS; j++)
		{
			if(args[i].compare(admin::args::POSSIBLE_ARGS[j]) == 0)
			{
				switch(j)
				{
				case HELP_ARG:
					admin::args::help();
					return 1;
				case START_ARG:
					if(args.size() > (i + 1))
					{
						SERVER_RUNS_FOR_SEC = strtol(args[i+1].c_str(),
													 NULL, 10);
					}
					else
					{
						// No Num specified, just run forever
						SERVER_RUNS_FOR_SEC = 0;
					}
					return 0;
				case UPDATE_DB_ARG:
					// dirty hack to start the db update bash script
					// note this is only *nix compatible
					system("./updateDB.sh");
					return 1;
				case CREATE_DB_ARG:
					hl::initDB();
					hl::shutdown();
					printf("Created a database file\n");
					return 1;
				case MAKE_SHOWS_ARG:
					/// @todo add ncurses based show editor call here
					admin::initSongEditor();
					return 1;
				}
			}
		}
	}
	// huh, bad args must've been passed, so quit
	return admin::args::badArgs();
}

static int fg_cX = 0, fg_cY = 0; // Cursor Location, file globals

// song editor launcher
int admin::initSongEditor()
{
	gui::init(); // init
	int inkey = getch(); // key just pressed
	while(inkey != '~')
	{
        inkey = getch();
		admin::songEditorEL(inkey);
		gui::updateGeneralGui();
	}
	gui::endGui(); // end
	std::cout << fg_cX << " " << fg_cY << std::endl;
	return 0;
}

void admin::songEditorEL(int inkey)
{
	// Cursor
	gui::printChrAt(fg_cY, fg_cX, ' '); // clear formar cursor pos
	if((inkey == KEY_LEFT) && (fg_cX > 0))
	{
        fg_cX--;
	}
	if((inkey == KEY_RIGHT) && (fg_cX < gui::SCR_WDTH))
	{
        fg_cX++;
	}
	if((inkey == KEY_UP) && (fg_cY > 0))
	{
        fg_cY--;
	}
	if((inkey == KEY_DOWN) && (fg_cY < gui::SCR_HGHT))
	{
        fg_cY++;
	}
	gui::printChrAt(fg_cY, fg_cX, '+'); // update cursor posistion
}

// --- Implementation of  admin::args functions below ---
std::vector<std::string> admin::args::createArgVector(int argc, char ** argv)
{
	std::vector<std::string> vec;
	for(int i = 1; i < argc; i++)
	{
		std::string s;
		int j = 0;
		while(argv[i][j] != '\0')
		{
			s += argv[i][j];
			j++;
		}
		vec.push_back(s);
	}
	return vec;
}

int admin::args::noArgs()
{
	printf("No args passed to program\n");
	printf("Usage: HolidayLights {args}\n");
	printf("See help for more information: HolidayLights --help\n");
	return ARG_FAIL;
}

int admin::args::badArgs()
{
	printf("Bad Args passed to program\n");
	printf("Usage: HolidayLights {args}\n");
	printf("See help for more information: HolidayLights --help\n");
	return ARG_FAIL;
}

int admin::args::help()
{
	using namespace std;
	cout << "--help\tPrints out the help message, then quits" << endl;
	cout << "--start n\tStarts the server and runs for n seconds" << endl;
	cout << "--updateDB\tUpdate the media table by grabbing metadata using a"
		 << "bash script. Then exits." << endl;
	cout << "--createDB\tCreates the database file then exit" << endl;
	cout << "--makeShow\tOpen the show editor program." << endl;
	return 0;
}
