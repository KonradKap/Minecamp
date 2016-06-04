/*
 * ButtonPrototypeTests.cc
 *
 *  Created on: 4 cze 2016
 *      Author: konrad
 */

#include <boost/test/unit_test.hpp>

#include "../../src/Button/ButtonPrototype.h"
#include "ofConstants.h"

BOOST_AUTO_TEST_SUITE(ButtonPrototypeTests);

BOOST_AUTO_TEST_CASE(getSizeShouldReturnSizeOfFirstImage)
{
	ofImage image;
	image.allocate(10, 20, ofImageType::OF_IMAGE_GRAYSCALE);
	ButtonPrototype prototype({image, image, image}, ofTrueTypeFont());
	BOOST_CHECK_EQUAL(prototype.getSize(), ofVec2f(10, 20));
}

BOOST_AUTO_TEST_SUITE_END();


