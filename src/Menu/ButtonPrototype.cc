/*
 * ButtonModel.cc
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#include "ButtonPrototype.h"

ButtonPrototype::ButtonPrototype() :
	image_(),
	font_()
{
}

ButtonPrototype::ButtonPrototype(const std::string& directory, const std::string& font_filename, const int font_size) :
	image_({ofImage(directory + "pressed.png"), ofImage(directory + "inactive.png"), ofImage(directory + "active.png")}),
	font_()
{
	font_.load(font_filename, font_size);
}

ButtonPrototype::ButtonPrototype(const ButtonPrototype& source) :
	image_(source.image_),
	font_(source.font_)
{
}

ButtonPrototype::~ButtonPrototype()
{
}

ofVec2f ButtonPrototype::getSize() const
{
	return ofVec2f(image_[0].getWidth(), image_[0].getHeight());
}

const std::array<ofImage, ButtonPrototype::COUNT>& ButtonPrototype::getImageArray() const
{
	return image_;
}

const ofTrueTypeFont& ButtonPrototype::getFont() const
{
	return font_;
}
/*
void ButtonModel::drawModel(const Button& button) const
{
	const ofVec2f POSITION = button.getPosition();
	const int INDEX = button.getState();
	const ofRectangle STRING_BOX = font_.getStringBoundingBox(button.getTitle(), 0, 0);
	image_[INDEX].draw(POSITION);
	font_.drawString(button.getTitle(), POSITION.x + image_[INDEX].getWidth()/2 - STRING_BOX.getWidth()/2,
									    POSITION.y + image_[INDEX].getHeight()/2 + STRING_BOX.getHeight()/2);
}
*/
