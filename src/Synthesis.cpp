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
#include <sqlite3.h>


// =============================================================================
// Synthesis Functions                                                         =
// Functions for visualizing sound                                             =
// @author Henry J Schmale                                                     =
// @date Jan 2015                                                              =
// =============================================================================

// parses a song
syn::ShowData* syn::parseSong(hl::SongData sd, int channels)
{
	return NULL;
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
