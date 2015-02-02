/** contains the necessary sql statements to run the database
 * @author Henry Schmale
 * @date January 11, 2015
 */

#ifndef SQL_CMDS_HPP_INCLUDED
#define SQL_CMDS_HPP_INCLUDED

namespace sql
{
/* Creates a table to hold the media metadata
* ID is the row id
* NAME is the name of the song
* PATH holds the relative file path from the current working dir to the song
*/
const char SQL_MEDIA_TB[] = "Create table if not exists MEDIA("
                            "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "NAME TEXT,"
                            "PATH TEXT);";

/* Creates a table to hold data about the microcontrollers in use
 * ID is the row id.
 * NAME is the prefered name of the device
 * IP_ADDRESS is the IP_ADDRESS of the effect on the Local Network
 * PORT is what port the clients are listening on for commands
 * CHANNELS is how many channels that controller has available
 * MAC is the MAC address of the device
 */
const char SQL_DEVICE_TB[] = "Create table if not exists DEVICES("
                             "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "NAME TEXT UNIQUE,"
                             "IP TEXT UNIQUE,"
                             "MAC TEXT UNIQUE,"
                             "PORT INTEGER,"
                             "CHANNELS INTEGER);";

// Selects a random song to load
const char SQL_SELECT_SONG[] = "Select * from MEDIA ORDER BY"
                               " RANDOM() LIMIT 1;";

// Selects the client devices in the database
const char SQL_SELECT_DEVICES[] = "Select * from DEVICES;";

// Callbacks

#ifdef SQL_NULL_CALLBACK
// This one does absolutely nothing
static int cbNull(void *NotUsed, int argc, char **argv, char **azColName)
{
    return 0;
}
#endif // SQL_NULL_CALLBACK
}



#endif // SQL_CMDS_HPP_INCLUDED
