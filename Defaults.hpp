/** \brief Contains the default configuration of program
 * \file Defaults.hpp
 * \author Henry Schmale
 * \date January 10, 2015
 */

#ifndef DEFAULTS_H_INCLUDED
#define DEFAULTS_H_INCLUDED

// Default Includes
#include <string>
#include <ctime>

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

const int CLIENT_WAIT_PERIOD = 100; //!< MS to wait between updates on client

// Network Defaults
const int SOCKET_TIMEOUT = 150;	//!< milliseconds before socket timesout

// INSTRUCTION DEFAULTS
const int BYTES_PER_INSTRUCT = 8; //!< bytes per instruction sent to client

// Song Generation Method
/** \brief Should shows be dynamically generated?
 */
const bool DYNAMIC_SHOW_GEN = true;

/** \brief a list of bit flags for checking bits. It's nice to have a list of
 * such things at hand.
 */
const long long BIT_FLAGS[64] = {0x1l,
								 0x2l,
								 0x4l,
								 0x8l,
								 0x10l,
								 0x20l,
								 0x40l,
								 0x80l,
								 0x100l,
								 0x200l,
								 0x400l,
								 0x800l,
								 0x1000l,
								 0x2000l,
								 0x4000l,
								 0x8000l,
								 0x10000l,
								 0x20000l,
								 0x40000l,
								 0x80000l,
								 0x100000l,
								 0x200000l,
								 0x400000l,
								 0x800000l,
								 0x1000000l,
								 0x2000000l,
								 0x4000000l,
								 0x8000000l,
								 0x10000000l,
								 0x20000000l,
								 0x40000000l,
								 0x80000000l,
								 0x100000000l,
								 0x200000000l,
								 0x400000000l,
								 0x800000000l,
								 0x1000000000l,
								 0x2000000000l,
								 0x4000000000l,
								 0x8000000000l,
								 0x10000000000l,
								 0x20000000000l,
								 0x40000000000l,
								 0x80000000000l,
								 0x100000000000l,
								 0x200000000000l,
								 0x400000000000l,
								 0x800000000000l,
								 0x1000000000000l,
								 0x2000000000000l,
								 0x4000000000000l,
								 0x8000000000000l,
								 0x10000000000000l,
								 0x20000000000000l,
								 0x40000000000000l,
								 0x80000000000000l,
								 0x100000000000000l,
								 0x200000000000000l,
								 0x400000000000000l,
								 0x800000000000000l,
								 0x1000000000000000l
								};

/** \brief Holds the current state of the server
 */
struct ServerData
{
	std::string m_currSong;	//!< Song currently playing
	std::string m_currShow;	//!< A Show string
	int m_waitPeriod;		//!< Seconds to wait before starting next show
	int m_clientsConnected; //!< Number of clients connected
	time_t m_serverStarted;	//!< When the server was started
	time_t m_songStarted;	//!< When the current song was started
	time_t m_now;			//!< What time is it?
};

// ============================================================================
// Default Function Prototypes
// ============================================================================

/** \brief allows the program to be shut down in a non standard way
 *
 * This will log the non standard shutdown to file then call shutdown functions
 * of various libriaries. Then print a stack trace on standard output of when
 * this function was quit
 * \param rc return code of the prog to the operating system
 * \todo Stack trace
 */
void emergencyShutdown(int rc);

// Other stuff yet to be thought of, probably config file defaults

#endif // DEFAULTS_H_INCLUDED
