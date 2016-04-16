/*
 * ButtonModel.h
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_BUTTONMODEL_H_
#define SRC_GAME_BUTTONMODEL_H_

#include <array>

#include "ofImage.h"
#include "ofTrueTypeFont.h"

class Button;

class ButtonModel
{
public:
	enum ButtonState
	{
		PRESSED,
		INACTIVE,
		ACTIVE,
		COUNT
	};

	ButtonModel();
	ButtonModel(const std::string& directory, const std::string& font_filename, const int font_size);
	ButtonModel(const ButtonModel& source);
	~ButtonModel();

	ButtonModel& operator= (const ButtonModel&) = default;

	ofVec2f getSize() const;

	const std::array<ofImage, ButtonState::COUNT>& getImageArray() const;
	const ofTrueTypeFont& getFont() const;

	void drawModel(const Button& button) const;
private:
	std::array<ofImage, ButtonState::COUNT> image_;
	ofTrueTypeFont font_;
};

#include "Game/Menu/Button.h"


#endif /* SRC_GAME_BUTTONMODEL_H_ */
