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
#include <cstdlib>
#include <dirent.h>
#include <errno.h>
#include <sqlite3.h>
#include <ncurses.h>
#include <cdk.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))


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
static CDKSCREEN *cdkscreen;
int syn::se::ShowEditor()
{
	WINDOW *screen;

	/* Initialize the Cdk screen.   */
	screen = initscr();
	cdkscreen = initCDKScreen (screen);

	/* Start CDK Colors */
	initCDKColor();

	// Begin shows
	syn::se::SelectShow();

	/* Clean up           */
	destroyCDKScreen (cdkscreen);
	endCDK();
	return 0;
}

// Menu to selectW a song
int syn::se::SelectShow()
{
	CDKVIEWER *viewer;
	const char * buttons[2] = {" Select", " Exit"};
	char * filesList[30];
	DIR *dp;
	dirent *dirp;
	if((dp = opendir("/home/hschmale")) == NULL)
	{
		exit(1);
	}
	int i;
	for(i = 0; ((i < 30) && ((dirp = readdir(dp)) != NULL)); i++)
	{
		filesList[i] = dirp->d_name;
	}
	closedir(dp);
	viewer = newCDKViewer(cdkscreen,
						  CENTER, CENTER, 22, 70,
						  buttons, 2, WA_STANDOUT | WA_BLINK,
						  true, false);
	setCDKViewer(viewer, "Select A Song File", filesList, sizeof(filesList),
				NULL, false, false, false);
	drawCDKViewer(viewer, true);
	i = activateCDKViewer(viewer, NULL);
	destroyCDKViewer(viewer);
	return 0;
}
