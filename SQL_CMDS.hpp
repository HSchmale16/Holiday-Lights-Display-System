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
	 */
	const char SQL_EFFECT_TB[] = "Create table if not exists EFFECTS("
								 "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
								 "NAME TEXT,"
								 "IP_ADDERESS,"
								 "PORT INTEGER,"
								 "CHANNELS INTEGER);";

	// Selects a random song to load
	const char SQL_SELECT_SONG[] = "Select name, path from MEDIA where row ="
								   "%d; ";
	// Callbacks
	// This one does absolutely nothing

}



#endif // SQL_CMDS_HPP_INCLUDED
