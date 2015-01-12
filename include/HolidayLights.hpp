#ifndef HOLIDAYLIGHTS_HPP_INCLUDED
#define HOLIDAYLIGHTS_HPP_INCLUDED

#include <string>
#include <vector>

// Holiday Lights Primary Namespace
// Contains all the functions that control the actual show
namespace HL
{
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

	/** \brief starts a show
	 *
	 * \return Nothing
	 * Selects a random show to run from the database depending on config
	 * settings.
	 */
	void startShow();

	/** \brief Shuts down the server
	 *
	 * \return nothing
	 * Terminates the database connection
	 */
	void shutdown();

	/// Struct for holding song data
	struct SongData
	{
		int m_songID;
		std::string m_name;
		std::string m_path;

		// ctor
		SongData() {};	// empty ctor
		SongData(int id, std::string name, std::string path)
		{
			m_songID = id;
			m_name = name;
			m_path = path;
		}
	};
}

#endif // HOLIDAYLIGHTS_HPP_INCLUDED
