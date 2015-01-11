/* pgm entry point
 * @author Henry Schmale
 * @date January 11, 2015
 */

#include <iostream>
#include "include/HolidayLights.hpp"
#include "include/Admin.hpp"

int main(int argc, char** argv)
{
	admin::parseArgs(argc, argv);
	return 0;
}
