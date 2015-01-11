/* Contains the functions to adminster this program
 * @author Henry Schmale
 * @date January 11, 2015
 */

#ifndef ADMIN_HPP_INCLUDED
#define ADMIN_HPP_INCLUDED

// Contains functions to administer this program
namespace admin
{
	/// Parses the command line args
	int parseArgs(int argc, char** argv);

	// Contains the command line arg parser functions
    namespace args
    {
		// prints help documentation
		void help();
    }
}

#endif // ADMIN_HPP_INCLUDED
