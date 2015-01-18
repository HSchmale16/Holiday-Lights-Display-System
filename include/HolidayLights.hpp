#ifndef HOLIDAYLIGHTS_HPP_INCLUDED
#define HOLIDAYLIGHTS_HPP_INCLUDED

#include <string>
#include <vector>

/// Holiday Lights Primary Namespace
/// Contains all the functions that control the actual show
namespace hl
{
	/// Struct for holding song data
	struct SongData
	{
		int m_songID;			//!< Song Id Number
		std::string m_name;		//!< Song File Name
		std::string m_path;		//!< Path to the song file

		// ctor
		SongData() {};	// empty ctor
		SongData(int id, std::string name, std::string path)
		{
			m_songID = id;
			m_name = name;
			m_path = path;
		}
	};

	/// Contains data about the client
	struct ClientDevice
	{
		std::string m_name;			//!< User friendly name
		std::string m_ipAddress;    //!< Ip Address of client
		int m_port;					//!< Port Client is listening on
		int m_channels;				//!< Number of output channels on that client
	};

	/** \brief initializes the lights system
	 *
	 * \return Absolutely Nothing
	 * Call this function before anything else in this header. It starts up the
	 * lighting system.
	 */
	void initLights();

	/** \brief Initializes the database
	 *
	 * \return Nothing
	 * This function makes the connection to the database, and creates the
	 * neccessary tables if they don't exist yet.
	 */
	void initDB();

	/** \brief Connects to the clients
	 *
	 * \return Manipulates global vector of clients
	 * This function pings all of the listed clients in the database.
	 * if it connects successfully, it adds the clients information to a global
	 * vector.
	 */
	void initClients();

	/** \brief starts a show
	 *
	 * \return Nothing
	 *
	 * Selects a random show to run from the database depending on config
	 * settings. Then depending on initial settings it either generates a new
	 * show or pulls a show from the database.
	 */
	void startShow();

	void sendShowToClient(ClientDevice cd);

	/** \brief Shuts down the server
	 *
	 * \return nothing
	 * Terminates the database connection
	 */
	void shutdown();

	// external globals
	extern SongData currSongDat;
}

#endif // HOLIDAYLIGHTS_HPP_INCLUDED
