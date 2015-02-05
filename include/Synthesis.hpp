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

/** \brief calculates the twiddle factor for dfts
 * \return a complex number containing the twiddle factor
 * \param N Number of samples
 * \param n it's the n in f(n)
 * \param k it's the current value of K
 */
std::complex<long double> twiddle(int N, int n, int k);

/** \brief calculates the discrete fourier transform on a set of data.
 * \return returns the phase at a specific point `n`
 * \param xk the data set to perform a dft on
 * \param N the size of the data set
 * \param n the `n` in f(n)
 * \param T the time period over which these samples were collected,
 *  how long it took to collect these samples.
 */
long long dft(short * xk, int N, int n, double T);

/** \brief parses a song into a light show
 * \param sd - A struct containing the song metadata.
 * \param channels - how many channels should the show be generated with
 * \param res - how many milliseconds should be sampled
 * \return a string that can be parsed by a client into a show
 */
std::string parseSong(hl::SongData &sd, int channels, int res);


/** \brief Performs analysis on a song
 * \param buff - section analyese
 * \param buffSz - Number of samples in buffer
 * \param channels - Only 2-channel audio is supported
 */
long long analysis(short *buff, int buffSz, int channels);

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
