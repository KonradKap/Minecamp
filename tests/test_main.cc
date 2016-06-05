/*
 * test_main.cc
 *
 *  Created on: 4 cze 2016
 *      Author: konrad
 */

#define BOOST_TEST_MODULE "C++ Unit Tests for MineCamp"

#ifdef __MINGW32__
// Mingw doesn't define putenv() needed by Boost.Test
extern int putenv(char*);
#endif

#include <boost/test/included/unit_test.hpp>
