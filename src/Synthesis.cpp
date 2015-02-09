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
#include "../include/FastMath.hpp"
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <dirent.h>
#include <errno.h>
#include <glog/logging.h>
#include <sqlite3.h>
#include <sndfile.hh>
#include <complex.h>
#include <fftw3.h>

// =============================================================================
// Synthesis Functions
// Functions for visualizing sound
// @author Henry J Schmale
// @date Jan 2015
// =============================================================================

const float PI = 3.14159265;

template<typename TYP>
void syn::pkdft(TYP * xt, TYP * pk, int n)
{
    TYP * iXk = new TYP[n];
    TYP * rXk = new TYP[n];

    /// Discrete Fourier Transform
    /// X(k) = sum(x(t) * e^(2 * Pi * k * t), 0, n)
    for(int k = 0; k < n; k++)
    {
        iXk[k] = 0;
        rXk[k] = 0;
        for(int t = 0; t < n; t++)
        {
            iXk[k] = (xt[t] * fm::fcos((2 * PI * k * t) / n));
            rXk[k] = (xt[t] * fm::fsin((2 * PI * k * t) / n));
        }
    }

    /// Calculate Power Spectrum
    /// P(k) = Re(X(k))^2 + Im(X(k))^2
    for(int k = 0; k < n; k++)
    {
        pk[k] = (rXk[k] * rXk[k]) + (iXk[k] * iXk[k]);
    }

    delete[] iXk;
    delete[] rXk;
}

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
    SndfileHandle file;
    file = SndfileHandle(sd.m_path.c_str());
    int buffSz = file.samplerate() * file.channels();
    LOG(INFO) << "song = " << sd.m_name << "\tBuff=" << buffSz;
    double *buff = new double[buffSz];
    while(file.read(buff, buffSz) == buffSz)
    {
        // perform analysis
        myCU.numericValue = syn::songAnalyze(buff, buffSz, channels,
                                             file.channels(),
                                             file.samplerate());
        for(unsigned int i = 0; i < sizeof(long long); i++)
        {
            show += myCU.byteValues[i];
        }
    }
    delete[] buff;
    return show;
}

// Not Used any more deprecated
long long syn::analysis(short *buff, int buffSz, int channels)
{
    long long myLong = 0;
    double average = 0;
    for(int i = 0; i < buffSz; i++)
    {
        average += buff[i];
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
    for(int i = 0; i < 64; i++)
    {
        if((rand() % 100) < percentToFlip)
        {
            myLong ^= BIT_FLAGS[i];
        }
    }
    return myLong;
}


template<typename TYP>
long long syn::songAnalyze(TYP * buff, int buffSz, int outChannels,
                           int inChannels, int sampleRate)
{
    // Check that the data is good to work with
    CHECK(inChannels > 0) << "inChannels cannot be 0";
    CHECK(outChannels > 0) << "outChannels cannot be 0";
    CHECK(outChannels <= 64) << "outChannels cannot be greater than 64";

    // allocate memory
    TYP * pk = new TYP[buffSz];
    for(int i = 0; i < buffSz; i++)
        pk[i] = 0;

    // Get Power Spectrum
    fftw_complex *out;
    fftw_plan p;
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * buffSz);
    p = fftw_plan_dft_r2c_1d(buffSz, buff, out, FFTW_ESTIMATE);
    fftw_execute(p);
    for(int i = 0; i < (buffSz / 2) + 1; i++){

    }

    // Analyze the power spectrum
    long long *counts = new long long[64];
    counts[0] = 0;
    int freqIncre = (sampleRate / 2) / outChannels; //!< Nyquelist's frequency
    int i = 0;
    for(int k = 0; k < buffSz; k++)
    {
        // calc freq for this value of k
        int freq = (k * sampleRate) / buffSz;
        if(freq > (freqIncre * (i + 1)))
        {
            i++;
            CHECK(i < 64) << "Buffer Overflow in analysis";
            counts[i] = 0; // 0 the next index, dyn alloc mem is not zeroed
        }
        counts[i] += pk[k];
    }

    // What lights do I light up?
    long long average = 0;
    for(i = 0; i < outChannels; i++)
    {
        average += counts[i];
    }
    average /= outChannels;

    long long lights = 0;
    for(i = 0; i < outChannels; i++)
    {
        if(counts[i] > average)
        {
            lights |= BIT_FLAGS[i];
        }
    }
    // deallocate memory, clean up
    delete[] counts;
    delete[] pk;
    fftw_destroy_plan(p);
    fftw_free(out);

    // return
    return lights;
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
