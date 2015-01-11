/** Implemenation of functions defined in ../include/admin.hpp
 * @author Henry Schmale
 * @date January 11, 2015
 */

#include "../include/Admin.hpp"
#include <cstdio>
#include <iostream>

int admin::parseArgs(int argc, char** argv)
{
	if(argc <= 1){
        printf("No args passed to program\n");
        printf("Usage: HolidayLights {args}\n");
        printf("See help for more information: HolidayLights --help\n");
	}
	return 0;
}
