/*
 * Button.h
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_BUTTON_H_
#define SRC_GAME_BUTTON_H_

#include <string>

#include "../Button/ButtonPrototype.h"
#include "Utill/Registrable.h"
#include "ofEvents.h"
#include "ofConstants.h"


class Button : public Registrable
{
public:
	Button(const ofVec2f& position, const std::string& title, const ButtonPrototype& base);
	Button(const Button& b);
	~Button();

	void setPosition(const ofVec2f& new_position);
	const ofVec2f& getPosition() const;

	void setTitle(const std::string& new_title);
	const std::string& getTitle() const;

	const ButtonPrototype& getPrototype() const;
	ButtonPrototype::ButtonState getState() const;
	ofEvent<const Button&>& getEvent();

	bool contains(const ofVec2f& point);

	void onMouseMove(ofMouseEventArgs& parameter);
	void onMousePress(ofMouseEventArgs& parameter);
	void onMouseRelease(ofMouseEventArgs& parameter);
private:
	void registerMe(const do_register_trait&);
	void unregisterMe(const do_register_trait&);

	ofEvent<const Button&> pressed_;

	ButtonPrototype::ButtonState state_;
	ofVec2f position_;
	std::string title_;

	const ButtonPrototype& base_;
};

#endif /* SRC_GAME_BUTTON_H_ */
