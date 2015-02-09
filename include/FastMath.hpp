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
namespace fm
{
/** \brief Fast SINE using lookup table
 */
template<typename TYP>
inline TYP fsin(TYP x);

/** \brief Fast COSINE using lookup table
 * \param x duh!
 */
template<typename TYP>
inline TYP fcos(TYP x);
}

#endif // FASTMATH_HPP_INCLUDED
