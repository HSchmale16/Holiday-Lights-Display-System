#ifndef HOLIDAYLIGHTS_HPP_INCLUDED
#define HOLIDAYLIGHTS_HPP_INCLUDED


// Holiday Lights Primary Namespace
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
	 * \param
	 * \param
	 * \return Nothing
	 *
	 */
	void startShow();
}

#endif // HOLIDAYLIGHTS_HPP_INCLUDED
