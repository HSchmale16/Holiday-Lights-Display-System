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

/** \brief Sound and waveform analysis functions are here
 *
 */
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


long long analysis(short *buff, int buffSz, int *peaks, int nPeaks);

/** \brief functions to work with the show editor
 */
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
