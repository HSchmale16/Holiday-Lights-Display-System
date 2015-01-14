// Implementation of functions defined in header of same name
// @author Henry Schmale
// @date January 10, 2015

#include "../include/HolidayLights.hpp"
#include "../Defaults.hpp"
#include "../SQL_CMDS.hpp"
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <SFML/Network.hpp>

// database connection
static sqlite3 * db;

// external globals
extern std::string NOW_PLAYING;

// This callback sets the global current song to be playing
hl::SongData currSongDat;
static int cbSong(void *NotUsed, int argc, char **argv, char **azColName)
{
	if(argc >= 3)
	{
		currSongDat.m_songID = strtol(argv[0], NULL, 10);
		currSongDat.m_name = argv[1];
		currSongDat.m_path = argv[2];
	}
	return 0;
}

// This callback tests for clients, pings them, then pushes them into a vector
std::vector<hl::ClientDevice> clients;
static int cbClients(void *NotUsed, int argc, char **argv, char **azColName)
{
	hl::ClientDevice cli;
	// fill in the struct
	if(argc >= 6)
	{
		cli.m_name = argv[1];
		cli.m_ipAddress = argv[2];
		cli.m_port = strtol(argv[4], NULL, 10);
		cli.m_channels = strtol(argv[5], NULL, 10);
		// PING
		sf::TcpSocket s;
		if(s.connect(sf::IpAddress(cli.m_ipAddress),
					 cli.m_port) == sf::Socket::Done)
		{
			// Sweet Success
			clients.push_back(cli);
		}
	}
	return 0;
}


// Holiday Lights Functions
void hl::initLights()
{
	hl::initDB();
	hl::initClients();
}

// initializes the database
void hl::initDB()
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
	rc = sqlite3_exec(db, sql::SQL_MEDIA_TB, sql::cbNull, 0, &z_ErrMsg);
	if(rc != SQLITE_OK)
	{
		std::cerr << "Failed to create MEDIA table." << std::endl;
		sqlite3_free(z_ErrMsg);
		exit(1);
	}
	// create the effects table
	rc = sqlite3_exec(db, sql::SQL_DEVICE_TB, sql::cbNull, 0, &z_ErrMsg);
	if(rc != SQLITE_OK)
	{
		std::cerr << "Failed to create EFFECTS table." << std::endl;
		sqlite3_free(z_ErrMsg);
		exit(SQL_FAIL);
	}
}

// initializes the clients
void hl::initClients()
{
	clients.clear();
	char * z_ErrMsg = 0;
	int rc = sqlite3_exec(db, sql::SQL_SELECT_DEVICES, cbClients, 0, &z_ErrMsg);
	if(rc)
	{
		sqlite3_free(z_ErrMsg);
		printf("Selection Fail on Devices\n");
		exit(SQL_FAIL);
	}
}

// starts a show
void hl::startShow()
{
	char *z_ErrMsg = 0;
	int rc = sqlite3_exec(db, sql::SQL_SELECT_SONG, cbSong, 0, &z_ErrMsg);
	if(rc)
	{
		sqlite3_free(z_ErrMsg);
		printf("FAIL!\n");
		exit(SQL_FAIL);
	}
	NOW_PLAYING = currSongDat.m_name;
}

// shuts down the system
void hl::shutdown()
{
	sqlite3_close(db);
	//std::cout << "Closed Database" << std::endl;
}
