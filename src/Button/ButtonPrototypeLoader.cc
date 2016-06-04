/*
 * ButtonPrototypeLoader.cc
 *
 *  Created on: 4 cze 2016
 *      Author: konrad
 */

#include "Button/ButtonPrototypeLoader.h"

//const std::array<const std::string, ButtonPrototype::ButtonState::COUNT> ButtonPrototypeLoader::NAMES =
//{"pressed", "inactive", "active"};

ButtonPrototypeLoader& ButtonPrototypeLoader::getInstance()
{
	static ButtonPrototypeLoader instance;
	return instance;
}

ButtonPrototype ButtonPrototypeLoader::load(const std::string& directory_name, const std::string& font_name, int font_size) const
{
	ofTrueTypeFont font;
	font.load(font_name, font_size);
	std::array<ofImage, ButtonPrototype::ButtonState::COUNT> images =
	{ofImage(directory_name + NAMES[0]),
	 ofImage(directory_name + NAMES[1]),
	 ofImage(directory_name + NAMES[2])};

	return ButtonPrototype(images, font);
}

ButtonPrototypeLoader::ButtonPrototypeLoader() :
	NAMES({"pressed" + EXTENSION,
		   "inactive" + EXTENSION,
		   "active" + EXTENSION})
{
}


