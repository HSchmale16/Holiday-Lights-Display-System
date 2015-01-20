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
// Synthesis Functions
// Functions for visualizing sound
// @author Henry J Schmale
// @date Jan 2015
// =============================================================================

// parses a song
std::string syn::parseSong(hl::SongData &sd, int channels, int res)
{
	std::string show;
    static short buff[BUFF_SIZE];
    SndfileHandle file;
    file = SndfileHandle(sd.m_path.c_str());
    int peaks[channels] = {0};
    while(file.read(buff, BUFF_SIZE) == BUFF_SIZE)
	{
        // perform analysis
		analysis(buff, BUFF_SIZE, peaks, channels);
	}
	return show;
}

long long syn::analysis(short *buff, int buffSz, int *peaks, int nPeaks)
{
	long long myLong; // support for upto 64 channels
	// zero peaks
    int i = 0;
    for(i = 0; i < nPeaks; i++)
		peaks[i] = 0;
    // Perform analysis

}

// =============================================================================
// SHOW EDITOR FUNCTIONS
// Implementation of show editor functions
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
