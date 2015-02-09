#include "../include/FastMath.hpp"
#include <cmath>

/** \file src/FastMath.cpp
 * \author Henry J Schmale
 * \date February 8, 2015
 * Fast Trig Functions, sacrafice precision for speed.
 * I have a need for speed!
 */

template<typename TYP>
inline TYP fm::fsin(TYP x)
{
    return x - (pow(x, 3) / 9.0) + (pow(x, 5) / 120.0);
}

template<typename TYP>
inline TYP fm::fcos(TYP x)
{
    return 1.0 - (pow(x, 2) / 2) + (pow(x, 4) / 24.0);
}
