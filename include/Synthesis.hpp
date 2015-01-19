/** @file Synthesis.hpp
 * @author Henry J Schmale
 * @date January 13, 2015
 * Contains functions for automatically generating shows based on frequency
 * analysis.
 */

#ifndef SYNTHESIS_HPP_INCLUDED
#define SYNTHESIS_HPP_INCLUDED

#include "HolidayLights.hpp"	// for the SongData Struct
#include <string>

// contains functions for analyising sound
namespace syn
{
struct ShowData
{
	int m_channels;		// How many channels this show has
	int m_resMilliSec;	// Resolution of song parse in milliseconds
	std::string m_data;	// Show data to send to client

	// ctor
	ShowData(int channels, std::string show)
	{
		m_channels = channels;
		m_data = show;
	}
};

/** \brief parses a song into a light show
 * \param sd - A struct containing the song metadata.
 * \param channels - how many channels should the show be generated with
 * \param res - how many milliseconds should be sampled
 * \return a string that can be parsed by a client into a show
 */
std::string parseSong(hl::SongData &sd, int channels, int res);

/** \brief performs super position on a set of 2 waves
 * \param ch1 - Channel 1 data
 * \param ch2 - Channel 2 data
 * \param ret - data to return
 * \param smp - number of samples in arrays
 * \return An array of samples of size smp
 */
void performSuperposition2Ch(short *ch1, short*ch2, short *ret, int smp);

// --- Show Editor Namespace ---
namespace se
{
// Show Editor Entry Point
int ShowEditor();

/** \brief Selects a show to a song to edit
 *
 * \return The id in the Media Table of the selected song - 0 on fail.
 * Shows an ncurses based menu of database options and asks user to
 * select a show to edit.
 */
int SelectShow();
} // end of show editor namespace
} // end of synth namespace

#endif // SYNTHESIS_HPP_INCLUDED
