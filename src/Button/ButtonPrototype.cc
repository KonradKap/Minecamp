/*
 * ButtonModel.cc
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#include <Button/ButtonPrototype.h>

ButtonPrototype::ButtonPrototype() :
	image_(),
	font_()
{
}

ButtonPrototype::ButtonPrototype(const std::array<ofImage, ButtonState::COUNT>& image, const ofTrueTypeFont& font) :
	image_(image),
	font_(font)
{
}
/*
ButtonPrototype::ButtonPrototype(const std::string& directory, const std::string& font_filename, const int font_size) :
	image_(),
	font_()
{
	font_.load(font_filename, font_size);
}
*/
ButtonPrototype::ButtonPrototype(const ButtonPrototype& source) :
	image_(source.image_),
	font_(source.font_)
{
}

ButtonPrototype& ButtonPrototype::operator= (ButtonPrototype source)
{
	swap(*this, source);
	return *this;
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

void swap(ButtonPrototype& first, ButtonPrototype& second)
{
	std::swap(first.image_, second.image_);
	std::swap(first.font_, second.font_);
}
