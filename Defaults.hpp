/** \brief Contains the default configuration of program
 * \file Defaults.hpp
 * \author Henry Schmale
 * \date January 10, 2015
 */

#ifndef DEFAULTS_H_INCLUDED
#define DEFAULTS_H_INCLUDED

// EXIT FAIL CODES
const int SQL_FAIL = 1;     //!< SQL Failure
const int FILE_FAIL =  2;	//!< Failed to do something with a file
const int ARG_FAIL  = 255;	//!< Something is wrong with the args passed to prog

// File Pathes - left as macros because it's cleaner for string constants
#define DB_FILE_PATH "lights.db" 			//!< Path to the database file
#define RESOURCES_PATH "resources/songs/"	//!< Path to resources directory

// Update Rates
const int UPDATE_T_PERIOD = 10;	//!< milliseconds to sleep each event loop

const int INTERMISSION = 10;	//!< Seconds to wait between shows

// Network Defaults
const int SOCKET_TIMEOUT = 150;	//!< milliseconds before socket timesout

// Song Generation Method
/** \brief Should shows be dynamically generated?
 */
const bool DYNAMIC_SHOW_GEN = true;

// Other stuff yet to be thought of, probably config file defaults

#endif // DEFAULTS_H_INCLUDED
