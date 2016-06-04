/*
 * ButtonModel.h
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_BUTTONMODEL_H_
#define SRC_GAME_BUTTONMODEL_H_

#include <array>
#include <cassert>

#include "ofImage.h"
#include "ofTrueTypeFont.h"

class Button;

class ButtonPrototype
{
public:
	enum ButtonState
	{
		PRESSED,
		INACTIVE,
		ACTIVE,
		COUNT
	};

	ButtonPrototype();
	ButtonPrototype(const std::string& directory, const std::string& font_filename, const int font_size);
	ButtonPrototype(const ButtonPrototype& source);
	~ButtonPrototype();

	ButtonPrototype& operator= (ButtonPrototype);

	friend void swap(ButtonPrototype& first, ButtonPrototype& second);

	ofVec2f getSize() const;

	const std::array<ofImage, ButtonState::COUNT>& getImageArray() const;
	const ofTrueTypeFont& getFont() const;

	//void drawModel(const Button& button) const;
private:
	std::array<ofImage, ButtonState::COUNT> image_;
	ofTrueTypeFont font_;
};

#include "Menu/Button.h"


#endif /* SRC_GAME_BUTTONMODEL_H_ */
