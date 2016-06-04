/*
 * ButtonTests.cc
 *
 *  Created on: 4 cze 2016
 *      Author: konrad
 */

#include <boost/test/unit_test.hpp>

#include "Button/Button.h"

BOOST_AUTO_TEST_SUITE(ButtonTests);

BOOST_AUTO_TEST_CASE(pointsWithinButtonShouldBeRecognized)
{
	ofImage image;
	image.allocate(10, 10, ofImageType::OF_IMAGE_COLOR);
	ButtonPrototype prototype({image, image, image}, ofTrueTypeFont());
	Button button(ofVec2f(0, 0), "", prototype);

	BOOST_CHECK(button.contains(ofVec2f(4, 4)));
}

BOOST_AUTO_TEST_CASE(pointsOustisdeButtonShouldNotBeRecognized)
{
	ofImage image;
	image.allocate(10, 10, ofImageType::OF_IMAGE_COLOR);
	ButtonPrototype prototype({image, image, image}, ofTrueTypeFont());
	Button button(ofVec2f(0, 0), "", prototype);

	BOOST_CHECK(!button.contains(ofVec2f(14, 14)));
}

BOOST_AUTO_TEST_CASE(mouseMovementOutsideOfButtonShouldKeepItInactive)
{
	ofImage image;
	image.allocate(10, 10, ofImageType::OF_IMAGE_COLOR);
	ButtonPrototype prototype({image, image, image}, ofTrueTypeFont());
	Button button(ofVec2f(0, 0), "", prototype);
	ofMouseEventArgs args(ofMouseEventArgs::Type::Moved, 15, 15);

	button.onMouseMove(args);

	BOOST_CHECK_EQUAL(button.getState(), ButtonPrototype::ButtonState::INACTIVE);
}

BOOST_AUTO_TEST_CASE(mouseMovementInsideOfButtonShouldMakeItActive)
{
	ofImage image;
	image.allocate(10, 10, ofImageType::OF_IMAGE_COLOR);
	ButtonPrototype prototype({image, image, image}, ofTrueTypeFont());
	Button button(ofVec2f(0, 0), "", prototype);
	ofMouseEventArgs args(ofMouseEventArgs::Type::Moved, 3, 3);

	button.onMouseMove(args);

	BOOST_CHECK_EQUAL(button.getState(), ButtonPrototype::ButtonState::ACTIVE);
}

BOOST_AUTO_TEST_CASE(mousePressOutsideOfButtonShouldHaveNoEffect)
{
	ofImage image;
	image.allocate(10, 10, ofImageType::OF_IMAGE_COLOR);
	ButtonPrototype prototype({image, image, image}, ofTrueTypeFont());
	Button button(ofVec2f(0, 0), "", prototype);
	ofMouseEventArgs args_moved(ofMouseEventArgs::Type::Moved, 16, 3);
	ofMouseEventArgs args_pressed(ofMouseEventArgs::Type::Pressed, 16, 3);

	button.onMouseMove(args_moved);
	button.onMousePress(args_pressed);

	BOOST_CHECK_EQUAL(button.getState(), ButtonPrototype::ButtonState::INACTIVE);
}

BOOST_AUTO_TEST_CASE(mousePressInsideOfButtonShouldMarkItAsPressed)
{
	ofImage image;
	image.allocate(10, 10, ofImageType::OF_IMAGE_COLOR);
	ButtonPrototype prototype({image, image, image}, ofTrueTypeFont());
	Button button(ofVec2f(0, 0), "", prototype);
	ofMouseEventArgs args_moved(ofMouseEventArgs::Type::Moved, 3, 3);
	ofMouseEventArgs args_pressed(ofMouseEventArgs::Type::Pressed, 3, 3);

	button.onMouseMove(args_moved);
	button.onMousePress(args_pressed);

	BOOST_CHECK_EQUAL(button.getState(), ButtonPrototype::ButtonState::PRESSED);
}

BOOST_AUTO_TEST_CASE(mouseReleaseOutsideOfButtonShouldHaveNoEffect)
{
	ofImage image;
	image.allocate(10, 10, ofImageType::OF_IMAGE_COLOR);
	ButtonPrototype prototype({image, image, image}, ofTrueTypeFont());
	Button button(ofVec2f(0, 0), "", prototype);
	ofMouseEventArgs args_moved(ofMouseEventArgs::Type::Moved, 13, 3);
	ofMouseEventArgs args_pressed(ofMouseEventArgs::Type::Pressed, 13, 3);
	ofMouseEventArgs args_released(ofMouseEventArgs::Type::Released, 13, 3);

	button.onMouseMove(args_moved);
	button.onMousePress(args_pressed);
	button.onMouseRelease(args_released);

	BOOST_CHECK_EQUAL(button.getState(), ButtonPrototype::ButtonState::INACTIVE);
}

BOOST_AUTO_TEST_CASE(mouseReleaseInsideOfButtonShouldMakeItActiveAgain)
{
	ofImage image;
	image.allocate(10, 10, ofImageType::OF_IMAGE_COLOR);
	ButtonPrototype prototype({image, image, image}, ofTrueTypeFont());
	Button button(ofVec2f(0, 0), "", prototype);
	ofMouseEventArgs args_moved(ofMouseEventArgs::Type::Moved, 3, 3);
	ofMouseEventArgs args_pressed(ofMouseEventArgs::Type::Pressed, 3, 3);
	ofMouseEventArgs args_released(ofMouseEventArgs::Type::Released, 3, 3);

	button.onMouseMove(args_moved);
	button.onMousePress(args_pressed);
	button.onMouseRelease(args_released);

	BOOST_CHECK_EQUAL(button.getState(), ButtonPrototype::ButtonState::ACTIVE);
}


BOOST_AUTO_TEST_SUITE_END();
