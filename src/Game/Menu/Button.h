/*
 * Button.h
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_BUTTON_H_
#define SRC_GAME_BUTTON_H_

#include <string>

#include "ofEvents.h"

#include "Game/Menu/ButtonModel.h"

class Button
{
public:
	Button();
	Button(const ofVec2f& position, const std::string& title, const ButtonModel* const base);
	Button(const Button& b);
	~Button();

	void setPosition(const ofVec2f& new_position);
	const ofVec2f& getPosition() const;

	void setTitle(const std::string& new_title);
	const std::string& getTitle() const;

	void setup();
	void bindModel(const ButtonModel* const base);

	ButtonModel::ButtonState getState() const;

	bool contains(const ofVec2f& point);
//TODO: overload with position given
	void draw() const;

	ofEvent<void> pressed;
private:
	void onMouseMove(ofMouseEventArgs& parameter);
	void onMousePress(ofMouseEventArgs& parameter);
	void onMouseRelease(ofMouseEventArgs& parameter);

	ButtonModel::ButtonState state_;
	ofVec2f position_;
	std::string title_;

	const ButtonModel* base_;
};

#endif /* SRC_GAME_BUTTON_H_ */
