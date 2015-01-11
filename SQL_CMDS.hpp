/** contains the necessary sql statements to run the database
 * @author Henry Schmale
 * @date January 11, 2015
 */

#ifndef SQL_CMDS_HPP_INCLUDED
#define SQL_CMDS_HPP_INCLUDED

/* Creates a table to hold the media metadata
 * ID is the row id
 * NAME is the name of the song
 * PATH holds the relative file path from the current working dir to the song
 */
const char MEDIA_TB[] = "Create table if not exists MEDIA("
						"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
						"NAME TEXT,"
						"PATH TEXT);";

/* Creates a table to hold data about the microcontrollers in use
 * ID is the row id.
 * NAME is the prefered name of the device
 * IP_ADDRESS is the IP_ADDRESS of the effect on the Local Network
 * PORT is what port the clients are listening on for commands
 * CHANNELS is how many channels that controller has available
 */
const char EFFECT_TB[] = "Create table if not exists EFFECTS("
						"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
						"NAME TEXT,"
						"IP_ADDERESS,"
						"PORT INTEGER,"
						"CHANNELS INTEGER);";

#endif // SQL_CMDS_HPP_INCLUDED
