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
#include <math.h>
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
	LOG(INFO) << "Begining Analysis of song with file path = " << sd.m_path;
	union ConversionUnion
	{
		long long numericValue;
		char byteValues[sizeof(long long)];
	} myCU;
	std::string show;
	static short buff[BUFF_SIZE];
	SndfileHandle file;
	file = SndfileHandle(sd.m_path.c_str());
	while(file.read(buff, BUFF_SIZE) == BUFF_SIZE)
	{
		// perform analysis
		myCU.numericValue = analysis(buff, BUFF_SIZE, channels);
		show += myCU.byteValues;
	}
	return show;
}

long long syn::analysis(short *buff, int buffSz, int channels)
{
	long long myLong = 0;
	double average = 0;
	for(int i = 0; i < buffSz; i++)
	{
		average += abs(buff[i]);
	}
	average /= buffSz;
	// determine amount of time that volume is higher than average
	int greaterThanAvg = 0;
	for(int i = 0; i < buffSz; i++)
	{
		if(buff[i] > average)
		{
			greaterThanAvg++;
		}
	}
	int percentToFlip = double(greaterThanAvg) / buffSz * 100;
	for(int i = 0; i < std::min(64, channels); i++)
	{
		if((rand() % 100) < percentToFlip)
			myLong ^= long(rand() * rand() * rand());
	}
	return myLong;
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
