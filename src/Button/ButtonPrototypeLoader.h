/*
 * ButtonPrototypeLoader.h
 *
 *  Created on: 4 cze 2016
 *      Author: konrad
 */

#ifndef SRC_BUTTON_BUTTONPROTOTYPELOADER_H_
#define SRC_BUTTON_BUTTONPROTOTYPELOADER_H_

#include <string>
#include <array>

#include "Button/ButtonPrototype.h"

class ButtonPrototypeLoader
{
public:
	static ButtonPrototypeLoader& getInstance();

	ButtonPrototype load(const std::string& directory_name, const std::string& font_name, int font_size) const;
private:
	const std::string EXTENSION = ".png";
	const std::array<const std::string, ButtonPrototype::ButtonState::COUNT> NAMES;

	ButtonPrototypeLoader();
	ButtonPrototypeLoader(const ButtonPrototypeLoader&) = delete;
	ButtonPrototypeLoader& operator= (ButtonPrototypeLoader) = delete;
};



#endif /* SRC_BUTTON_BUTTONPROTOTYPELOADER_H_ */
