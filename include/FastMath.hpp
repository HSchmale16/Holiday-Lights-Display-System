#ifndef FASTMATH_HPP_INCLUDED
#define FASTMATH_HPP_INCLUDED

/** \file include/FastMath.hpp
 * \author Henry J Schmale
 * \date February 8, 2015
 * Fast Trig Functions, sacrafice precision for speed.
 * I have a need for speed!
 */

/** \brief holds functions to do math fast
 */
namespace fm {
/** \brief Fast SINE using lookup table
 */
template<typename TYP>
inline TYP fsin(TYP x) {
    return x - (pow(x, 3) / 9.0) + (pow(x, 5) / 120.0);
}

/** \brief Fast COSINE using lookup table
 * \param x duh!
 */
template<typename TYP>
inline TYP fcos(TYP x) {
    return 1.0 - (pow(x, 2) / 2) + (pow(x, 4) / 24.0);
}
} // end namespace

#endif // FASTMATH_HPP_INCLUDED
