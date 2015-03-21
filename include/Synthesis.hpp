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
#include <cmath>
#include <complex>

/** \brief Sound and waveform analysis functions are here
 *
 */
namespace syn {

/** \brief I'm not sure what this is for, but I'm not touching this.
 */
struct ShowData {
    int m_channels;		//!< How many channels this show has
    int m_resMilliSec;	//!< Resolution of song parse in milliseconds
    std::string m_data;	//!< Show data to send to client

    // ctor
    ShowData(int channels, std::string show) {
        m_channels = channels;
        m_data = show;
    }
};

/** \brief Performs a discrete fourier transform on a set of real numbers
 * \return the power spectrum of the dft derived from the data via pointer.
 * \param xt The set of _real_ numbers to analyeze.
 * \param pk The set of return set, This will hold the power spectrum.
 * \param n The number of elements in the data set.
 * \note pk must have same __amount or more__ space allocated as xt
 */
template<typename TYP>
void pkdft(TYP * xt, TYP * pk, int n);

/** \brief parses a song into a light show
 * \param sd - A struct containing the song metadata.
 * \param channels - how many channels should the show be generated with
 * \param res - how many milliseconds should be sampled
 * \return a string that can be parsed by a client into a show
 */
std::string parseSong(hl::SongData &sd, int channels, int res);


/** \deprecated This function is now deprecated due to being absolute crap at
 * analyzing a song section. It didn't work accurately at all, and depended on
 * the volume of the song more than anything else. It's implementation is very
 * limited in what it supports, so it's been replaced with a templeted function
 * which uses a dft.
 * \brief Performs analysis on a song
 * \param buff - section analyese
 * \param buffSz - Number of samples in buffer
 * \param channels - Only 2-channel audio is supported
 */
long long analysis(short *buff, int buffSz, int channels);

/** \brief This function performs analysis on a section of a song by using a dft
 * and interpreting the data returned with minimum required level filter, and
 * will custom design the output based on how many channels it can output on.
 * \return The lights that should be light as a 64 bit string.
 * \param buff The data to analyse.
 * \param buffSz Elements in buff
 * \param outChannels number of channels on clientdevice, __64 channels max__.
 * \param inChannels number of channels in the song, _limited to 2 for now_
 * \param sampleRate the sample rate of the data being analyzed
 *
 * This function generates the show based on what frequencies make up the
 * section that is to be analyzed.
 */
template<typename TYP>
long long songAnalyze(TYP * buff, int buffSz, int outChannels,
                      int inChannels, int sampleRate);

// ======================== New Namespace ===================================
/** \brief functions to work with the show editor
 */
namespace se {
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
