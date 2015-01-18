// Contains the default configuration of program
// @author Henry Schmale
// @date January 10, 2015

#ifndef DEFAULTS_H_INCLUDED
#define DEFAULTS_H_INCLUDED

// EXIT FAIL CODES
#define SQL_FAIL 1      // SQL Failure
#define FILE_FAIL 2		// Failed to do something with a file
#define ARG_FAIL 255	// Something is wrong with the args passed to prog

// File Pathes
#define DB_FILE_PATH "lights.db"
#define RESOURCES_PATH "resources/songs/"

// Update Rates
#define UPDATE_T_PERIOD 10	// milliseconds to sleep each event loop, reduces
// CPU Usage

#define INTERMISSION 10		// Seconds to wait between shows

// Network Defaults
#define SOCKET_TIMEOUT 150	// milliseconds before socket timesout

// Other stuff yet to be thought of, probably config file defaults

#endif // DEFAULTS_H_INCLUDED
