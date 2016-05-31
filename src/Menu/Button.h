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

#include "Menu/ButtonModel.h"

//TODO: change that const ptr to const reference
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

	void bindModel(const ButtonModel* const base);
	const ButtonModel* getModel() const;

	ButtonModel::ButtonState getState() const;
	ofEvent<const Button&>& getEvent();

	bool contains(const ofVec2f& point);

private:
	void setup();

	void onMouseMove(ofMouseEventArgs& parameter);
	void onMousePress(ofMouseEventArgs& parameter);
	void onMouseRelease(ofMouseEventArgs& parameter);

	ofEvent<const Button&> pressed_;

	ButtonModel::ButtonState state_;
	ofVec2f position_;
	std::string title_;

	const ButtonModel* base_;
};

#endif /* SRC_GAME_BUTTON_H_ */
