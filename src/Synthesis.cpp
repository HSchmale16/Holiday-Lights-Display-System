/** @file Synthesis.cpp
 * @author Henry J Schmale
 * @date January 13, 2015
 * Contains implementations of functions for automatically generating shows
 * based on frequency analysis.
 */

#include "../include/Synthesis.hpp"
#include "../include/HolidayLights.hpp"
#include "../Defaults.hpp"
#include "../SQL_CMDS.hpp"
#include <iostream>
#include <cstdlib>
#include <dirent.h>
#include <errno.h>
#include <glog/logging.h>
#include <sqlite3.h>
#include <sndfile.hh>

// =============================================================================
// Synthesis Functions                                                         =
// Functions for visualizing sound                                             =
// @author Henry J Schmale                                                     =
// @date Jan 2015                                                              =
// =============================================================================

// parses a song
std::string syn::parseSong(hl::SongData &sd, int channels, int res)
{
    std::string show;
	SF_INFO info;
	SNDFILE *file;
	if(!(file = sf_open(sd.m_path.c_str(), SFM_READ, &info)))
	{
        LOG(ERROR) << "Couldn't open file: " << sd.m_path;
	}


	sf_close(file);
	return show;
}

// =============================================================================
// SHOW EDITOR FUNCTIONS                                                       =
// Implementation of show editor functions                                     =
// =============================================================================

// Show Editor Entry Point
int syn::se::ShowEditor()
{
	return 0;
}

// Menu to selectW a song
int syn::se::SelectShow()
{
	return 0;
}
