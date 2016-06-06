/*
 * ButtonTests.cc
 *
 *  Created on: 4 cze 2016
 *      Author: konrad
 */

#include <boost/test/unit_test.hpp>


#include "../Menu/Button.h"

BOOST_AUTO_TEST_SUITE(ButtonTests);

BOOST_AUTO_TEST_CASE(defaultConstructorShouldFillWithZeros)
{
	ButtonPrototype prototype;
	Button button(ofVec2f(0, 0), "", prototype);
}

BOOST_AUTO_TEST_SUITE_END();
