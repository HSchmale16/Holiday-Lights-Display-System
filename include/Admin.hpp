/* Contains the functions to adminster this program
 * @author Henry Schmale
 * @date January 11, 2015
 */

#ifndef ADMIN_HPP_INCLUDED
#define ADMIN_HPP_INCLUDED

#include <vector>	// for holding args
#include <string>	// args

// Contains functions to administer this program
namespace admin
{
	/** \brief Parses the command line arguements
	 *
	 * \param argc - arguement count
	 * \param argv - args array
	 * \return 0 on success, Anything else is bad
	 * Compares the args and sets the appropiate flags in the program based on
	 * arguements passed
	 */
	int parseArgs(int argc, char** argv);

	// Contains the command line arg parser functions
	namespace args
	{
		/** \brief Creates a vector of strings from arguements passed
		 * \note it skips the 0th arguement (prog name)
		 * \param argc - arguement count
		 * \param argv - args array
		 * \return A vector of strings containing the args passed for easy comps
		 *
		 */
		std::vector<std::string> createArgVector(int argc, char **argv);

		// No args passed. Prints the err message
		int noArgs();

		// bad args were passed
		int badArgs();

		// prints help documentation
		int help();

		// Arguement List
		const unsigned int NUM_POSSIBLE_ARGS = 5;
		const std::string POSSIBLE_ARGS[] =
		{
			"--help",		// Print Help the Quit
			"--start",		// Starts the server process for n seconds
			"--updateDB",	// Update the database
			"--createDB",	// Creates the database file then exit
			"--makeShows"	// Make a new show
		};
		// Arguement Codes
#define HELP_ARG 0
#define START_ARG 1
#define UPDATE_DB_ARG 2
#define CREATE_DB_ARG 3
#define MAKE_SHOWS_ARG 4
	}
}

#endif // ADMIN_HPP_INCLUDED
