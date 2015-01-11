// Implementation of functions defined in header of same name
// @author Henry Schmale
// @date January 10, 2015

#include "../include/HolidayLights.hpp"
#include "../Defaults.hpp"
#include "../SQL_CMDS.hpp"
#include <sqlite3.h>
#include <cstdlib>
#include <iostream>

// database connection
static sqlite3 * db;

void HL::initLights()
{
	HL::initDB();
}

// initializes the database
void HL::initDB()
{
	int rc = sqlite3_open(DB_FILE_PATH, &db);
	if(rc)
	{
		std::cerr << "Couldn't open database. Terminating..." << std::endl;
		exit(1);
	}
}
