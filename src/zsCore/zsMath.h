//
// Created by Mokhairy on 7/26/2020.
//

#ifndef ZSIM_ZSMATH_H
#define ZSIM_ZSMATH_H

#include "zsCore/zsForwardDeclarations.h"

//#define _USE_MATH_DEFINES
#include <cmath>
#include <complex>

namespace zsim{
/** @namespace zsim::math

    @brief
    This namespace contains common mathematical functions.

    \ingroup Core
*/
    namespace math{
        typedef std::numeric_limits<real_t> limits;

// Math functions
        using std::abs;
        using std::acos;
        using std::asin;
        using std::atan2;
        using std::atan;
        using std::ceil;
        using std::cos;
        using std::cosh;
        using std::exp;
        using std::floor;
        using std::frexp;
        using std::ldexp;
        using std::log10;
        using std::log;
        using std::max;
        using std::min;
        using std::pow;
        using std::sin;
        using std::sinh;
        using std::sqrt;
        using std::tan;
        using std::tanh;
        using std::real;
        using std::imag;
        using std::conj;

#ifdef ZSIM_WITH_CODIPACK
using codi::abs;
using codi::acos;
using codi::asin;
using codi::atan2;
using codi::atan;
using codi::ceil;
using codi::cos;
using codi::cosh;
using codi::exp;
using codi::floor;
//using codi::frexp;
//using codi::ldexp;
using codi::log10;
using codi::log;
using codi::max;
using codi::min;
using codi::pow;
using codi::sin;
using codi::sinh;
using codi::sqrt;
using codi::tan;
using codi::tanh;
#endif

#ifdef ZSIM_WITH_UNUM
using sw::unum::abs;
using sw::unum::acos;
using sw::unum::asin;
using sw::unum::atan2;
using sw::unum::atan;
using sw::unum::ceil;
using sw::unum::cos;
using sw::unum::cosh;
using sw::unum::exp;
using sw::unum::floor;
//using sw::unum::frexp;
//using sw::unum::ldexp;
using sw::unum::log10;
using sw::unum::log;
using sw::unum::max;
using sw::unum::min;
using sw::unum::pow;
using sw::unum::sin;
using sw::unum::sinh;
using sw::unum::sqrt;
using sw::unum::tan;
using sw::unum::tanh;


// dummy
template<size_t nbits, size_t es>
inline sw::unum::posit<nbits,es> frexp(const sw::unum::posit<nbits,es> & a, int* b) {return  a;}

template<size_t nbits, size_t es>
inline sw::unum::posit<nbits,es> ldexp(const sw::unum::posit<nbits,es> & a, int b ) {return  a;}

using sw::unum::isnan;
using sw::unum::isfinite;
using sw::unum::isinf;

using sw::unum::real;
using sw::unum::imag;
using sw::unum::conj;

#endif


        template <typename T>
        struct numeric_limits
        {
            inline static int digits()
            { return std::numeric_limits<T>::digits; }

            inline static int digits10()
            { return std::numeric_limits<T>::digits10; }
        };

#ifdef GISMO_WITH_MPFR
        template <>
struct numeric_limits<mpfr::mpreal>
{
    inline static int digits()
    { return std::numeric_limits<mpfr::mpreal>::digits(); }

    inline static int digits10()
    { return std::numeric_limits<mpfr::mpreal>::digits10(); }
};
#endif

#define REAL_DIG math::numeric_limits<real_t>::digits10()

    }

}


#endif //ZSIM_ZSMATH_H
