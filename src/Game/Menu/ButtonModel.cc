/*
 * ButtonModel.cc
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#include "Game/Menu/ButtonModel.h"

ButtonModel::ButtonModel(const std::string& directory, const std::string& font_filename, const int font_size) :
	image_({ofImage(directory + "/pressed.png"), ofImage(directory + "/inactive.png"), ofImage(directory + "/active.png")}),
	font_()
{
	font_.load(font_filename, font_size);
}

ButtonModel::~ButtonModel()
{
}

ofVec2f ButtonModel::getSize() const
{
	return ofVec2f(image_[0].getWidth(), image_[0].getHeight());
}

const std::array<ofImage, ButtonModel::COUNT>& ButtonModel::getImageArray() const
{
	return image_;
}

const ofTrueTypeFont& ButtonModel::getFont() const
{
	return font_;
}

void ButtonModel::drawModel(const Button& button) const
{
	const ofVec2f POSITION = button.getPosition();
	const int INDEX = button.getState();
	const ofRectangle STRING_BOX = font_.getStringBoundingBox(button.getTitle(), 0, 0);
	image_[INDEX].draw(POSITION);
	font_.drawString(button.getTitle(), POSITION.x + image_[INDEX].getWidth()/2 - STRING_BOX.getWidth()/2,
									    POSITION.y + image_[INDEX].getHeight()/2 + STRING_BOX.getHeight()/2);
}

