//
// Created by Mokhairy on 7/27/2020.
//

#ifndef ZSIM_ZSIM_UNITTEST_H
#define ZSIM_ZSIM_UNITTEST_H
/** @file test.h
 *
 * This file provides a transitive include for the UnitTest++ library
 * so that you don't need to remember how to include it yourself. This
 * file also provides you with a reference for using UnitTest++.
 *
 * == BASIC REFERENCE ==
 *      - TEST(NAME_OF_TEST) { body_of_test }
 *      - TEST_FIXTURE(NAME_OF_FIXTURE,NAME_OF_TEST){ body_of_test }
 *
 * == CHECK MACRO REFERENCE ==
 *      - CHECK(EXPR);
 *      - CHECK_EQUAL(EXPECTED,ACTUAL);
 *      - CHECK_CLOSE(EXPECTED,ACTUAL,EPSILON);
 *      - CHECK_ARRAY_EQUAL(EXPECTED,ACTUAL,LENGTH);
 *      - CHECK_ARRAY_CLOSE(EXPECTED,ACTUAL,LENGTH,EPSILON);
 *      - CHECK_ARRAY2D_EQUAL(EXPECTED,ACTUAL,ROWCOUNT,COLCOUNT);
 *      - CHECK_ARRAY2D_CLOSE(EXPECTED,ACTUAL,ROWCOUNT,COLCOUNT,EPSILON);
 *      - CHECK_THROW(EXPR,EXCEPTION_TYPE_EXPECTED);
 *
 * == TIME CONSTRAINTS ==
 *
 *      - UNITTEST_TIME_CONSTRAINT(TIME_IN_MILLISECONDS);
 *      - UNITTEST_TIME_CONSTRAINT_EXEMPT();
 *
 * == MORE INFO ==
 *      See: http://unittest-cpp.sourceforge.net/UnitTest++.html
 */

#include "zsim.h"

#include "UnitTest++.h"
#include "zs/CheckMacros.h"
#include "zs/SuppressOutput.h"

using namespace zsim;

/* Logging messages, disabled by default */
#ifdef TEST_INFO
#define zsTestInfo std::cout
#else
#define zsTestInfo if (0) std::cerr
#endif

/* Tolerance for approximate comparison */
extern const real_t EPSILON;

#endif //ZSIM_ZSIM_UNITTEST_H
