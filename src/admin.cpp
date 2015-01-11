/** Implemenation of functions defined in ../include/admin.hpp
 * @author Henry Schmale
 * @date January 11, 2015
 */

#include "../include/Admin.hpp"
#include "../Defaults.hpp"
#include "../include/HolidayLights.hpp" // for db commands
#include <cstdio>
#include <iostream>
#include <cstdlib>

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
                    system("./updateDB.sh");
                    return 1;
				case CREATE_DB_ARG:
                    HL::initDB();
                    HL::shutdown();
                    printf("Created a database file\n");
                    return 1;
				}
			}
		}
	}
	// huh, bad args must've been passed, so quit
	admin::args::badArgs();
	return 1;
}

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
	return 0;
}
