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
		int m_channels;
		std::string m_data;

		// ctor
		ShowData(int channels, std::string show)
		{
			m_channels = channels;
			m_data = show;
		}
	};

	ShowData parseSong(hl::SongData sd, int channels);
}

#endif // SYNTHESIS_HPP_INCLUDED
