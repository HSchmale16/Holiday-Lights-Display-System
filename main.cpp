/* pgm entry point
 * @author Henry Schmale
 * @date January 11, 2015
 */

#include <iostream>
#include "include/HolidayLights.hpp"
#include "include/Admin.hpp"
#include "Defaults.hpp"

int SERVER_RUNS_FOR_SEC;

int main(int argc, char** argv)
{
	// check if the args passed from terminal were bad
	if(admin::parseArgs(argc, argv))
	{
        return 0; // if so quit
	}
	return 0;
}
