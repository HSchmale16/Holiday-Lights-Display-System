// Implementation of functions defined in header of same name
// @author Henry Schmale
// @date January 10, 2015

#define SQL_NULL_CALLBACK
#include "../include/HolidayLights.hpp"
#include "../include/Synthesis.hpp"
#include "../include/ClientDevice.h"     //!< The Client Device Class Header
#include "../Defaults.hpp"
#include "../SQL_CMDS.hpp"
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <SFML/Network.hpp>
#include <glog/logging.h>
#include <SFML/Audio.hpp>

// database connection
static sqlite3 * db;

// This callback sets the global current song to be playing
hl::SongData hl::currSongDat;
static int cbSong(void *NotUsed, int argc, char **argv, char **azColName) {
    if(argc >= 3) {
        hl::currSongDat.m_songID = strtol(argv[0], NULL, 10);
        hl::currSongDat.m_name = std::string(argv[1]);
        hl::currSongDat.m_path = std::string(argv[2]);
    }
    return 0;
}

// This callback tests for clients, pings them, then pushes them into a vector
// For usage later
std::vector<hl::ClientDevice> clients;
static int cbClients(void *NotUsed, int argc, char **argv, char **azColName) {
    // fill in the struct
    if(argc >= 6) {
        hl::ClientDevice cli;
        cli.m_name = argv[1];
        cli.m_ipAddress = argv[2];
        cli.m_port = strtol(argv[4], NULL, 10);
        cli.m_channels = strtol(argv[5], NULL, 10);
        // PING
        sf::TcpSocket s;
        if(s.connect(sf::IpAddress(cli.m_ipAddress),
                     cli.m_port,
                     sf::milliseconds(SOCKET_TIMEOUT)) == sf::Socket::Done) {
            // Sweet Success
            clients.push_back(cli);
            LOG(INFO) << "Added client at " << cli.m_ipAddress
                      << " listening on port " << cli.m_port;
        } else {
            LOG(WARNING) << "There is a bad client in the database. Client Name"
                         << " is " << cli.m_name;
        }
    } else { // Something went wrong in the client device sql querry
        LOG(ERROR) << "There weren't enough arguements returned by the SQL"
                   << " Querry to the Clients Table.";
    }
    return 0;
}


// Holiday Lights Functions
void hl::initLights() {
    hl::initDB();
    hl::initClients(); // this can be very time consuming
}

// initializes the database
void hl::initDB() {
    // connect to the database
    int rc = sqlite3_open(DB_FILE_PATH, &db);
    char *z_ErrMsg = 0;
    if(rc) {
        LOG(ERROR) << "Couldn't open database. Terminating...";
        exit(SQL_FAIL);
    }
    LOG(INFO) << "Opened database successfully";
    // create the tables - First is the media table
    rc = sqlite3_exec(db, sql::SQL_MEDIA_TB, sql::cbNull, 0, &z_ErrMsg);
    if(rc != SQLITE_OK) {
        LOG(ERROR) << "Failed to create MEDIA table.";
        sqlite3_free(z_ErrMsg);
        exit(1);
    }
    // create the effects table
    rc = sqlite3_exec(db, sql::SQL_DEVICE_TB, sql::cbNull, 0, &z_ErrMsg);
    if(rc != SQLITE_OK) {
        LOG(ERROR) << "Failed to create EFFECTS table.";
        sqlite3_free(z_ErrMsg);
        exit(SQL_FAIL);
    }
}

// initializes the clients
void hl::initClients() {
    clients.clear();
    char * z_ErrMsg = 0;
    int rc = sqlite3_exec(db, sql::SQL_SELECT_DEVICES, cbClients, 0, &z_ErrMsg);
    if(rc) {
        sqlite3_free(z_ErrMsg);
        LOG(INFO) << "A problem occured with selection querry on the devices"
                  << " table.";
        exit(SQL_FAIL);
    }
    // There had better be some clients to talk to.
    CHECK(clients.size() > 0) << "There were no clients to talk to. "
                              << "This effort is futile. So I Quit.";
    if(clients.size() == 0) {
        LOG(WARNING) << "There are 0 clients connected.";
    }
}

// starts a show
sf::Music music;
int hl::startShow() {
    int waitPeriod = 0;;
    char *z_ErrMsg = 0;
    int rc = sqlite3_exec(db, sql::SQL_SELECT_SONG, cbSong, 0, &z_ErrMsg);
    if(rc) {
        sqlite3_free(z_ErrMsg);
        LOG(FATAL) << "Failed to fetch a song from the database";
        exit(SQL_FAIL);
    }
    if(!music.openFromFile(currSongDat.m_path)) {
        LOG(ERROR) << "Failed to load song: " << currSongDat.m_path;
    }
    // create a show
    unsigned int i;
    std::vector<std::string> shows;
    for(i = 0; i < clients.size(); i++) {
        std::string shStr = syn::parseSong(currSongDat, clients[i].m_channels,
                                           100);
        CHECK(shStr.length() > 1);
        shows.push_back(shStr);
        waitPeriod = shStr.length() / BYTES_PER_INSTRUCT;
        serverstate.m_currShow = shStr;
    }
    // send the show
    for(i = 0; i < shows.size(); i++) {
        hl::sendShowToClient(clients[i], shows[i]);
    }
    music.play();
    return waitPeriod;
}

// Sends data to a client
void hl::sendShowToClient(ClientDevice cd , std::string show) {
    sf::TcpSocket s;

    if(s.connect(sf::IpAddress(cd.m_ipAddress),
                 cd.m_port,
                 sf::milliseconds(SOCKET_TIMEOUT)) != sf::Socket::Done) {
        LOG(ERROR) << "Failed to connect to client at " << cd.m_ipAddress
                   << " listening on port " << cd.m_port;
        return; // return because no use in waiting
    }
    // send the data
    if(s.send(show.c_str(), show.length()) != sf::Socket::Done) {
        LOG(ERROR) << "Failed to send show to client";
    } else {
        // Success on sending data log to file
        LOG(INFO) << "Sent show data to " << cd.m_name << " at "
                  << cd.m_ipAddress << " listening on port " << cd.m_port
                  << " with name "<< cd.m_name;
    }
}


// shuts down the system
void hl::shutdown() {
    sqlite3_close(db);
    LOG(INFO) << "Closed the database file";
}
