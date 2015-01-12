// Implementation of functions defined in header of same name
// @author Henry Schmale
// @date January 10, 2015

#include "../include/HolidayLights.hpp"
#include "../Defaults.hpp"
#include "../SQL_CMDS.hpp"
#include <sqlite3.h>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

// database connection
static sqlite3 * db;

// external globals
extern std::string NOW_PLAYING;

// Db Callbacks
static int cbNull(void *NotUsed, int argc, char **argv, char **azColName)
{
	return 0;
}

std::vector<std::string> cbSongRet;
static int cbSong(void *NotUsed, int argc, char **argv, char **azColName)
{
	std::string str = argv[0];
	cbSongRet.push_back(str);
	str = argv[1];
	cbSongRet.push_back(str);
    return 0;
}

// Holiday Lights Functions
void HL::initLights()
{
	HL::initDB();
}

// initializes the database
void HL::initDB()
{
	// connect to the database
	int rc = sqlite3_open(DB_FILE_PATH, &db);
	char *z_ErrMsg = 0;
	if(rc)
	{
		std::cerr << "Couldn't open database. Terminating..." << std::endl;
		exit(SQL_FAIL);
	}
	// create the tables - First is the media table
	rc = sqlite3_exec(db, sql::SQL_MEDIA_TB, cbNull, 0, &z_ErrMsg);
	if(rc != SQLITE_OK)
	{
		std::cerr << "Failed to create MEDIA table." << std::endl;
		sqlite3_free(z_ErrMsg);
		exit(1);
	}
	// create the effects table
	rc = sqlite3_exec(db, sql::SQL_EFFECT_TB, cbNull, 0, &z_ErrMsg);
	if(rc != SQLITE_OK)
	{
		std::cerr << "Failed to create EFFECTS table." << std::endl;
		sqlite3_free(z_ErrMsg);
		exit(SQL_FAIL);
	}
}

// starts a show
void HL::startShow()
{
	//cbSongRet.clear();
	char *z_ErrMsg = 0;
	int rc = sqlite3_exec(db, sql::SQL_SELECT_SONG, cbSong, 0, &z_ErrMsg);
	if(rc)
	{
		sqlite3_free(z_ErrMsg);
		printf("FAIL!\n");
		exit(SQL_FAIL);
	}
	NOW_PLAYING = cbSongRet[0];
}

// shuts down the system
void HL::shutdown()
{
	sqlite3_close(db);
	//std::cout << "Closed Database" << std::endl;
}
