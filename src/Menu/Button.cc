/*
 * Button.cc
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#include "Menu/Button.h"
/*
Button::Button() :
	state_(ButtonPrototype::INACTIVE), position_(), title_(), base_()
{
	setup();
}
*/
Button::Button(const ofVec2f& position, const std::string& title, const ButtonPrototype& base) :
	state_(ButtonPrototype::INACTIVE),
	position_(position),
	title_(title),
	base_(base)
{
	setup();
}

Button::Button(const Button& b) :
	state_(b.state_), position_(b.position_), title_(b.title_), base_(b.base_)
{
	setup();
}

Button::~Button()
{
	ofRemoveListener(ofEvents().mouseMoved, this, &Button::onMouseMove);
	ofRemoveListener(ofEvents().mousePressed, this, &Button::onMousePress);
	ofRemoveListener(ofEvents().mouseReleased, this, &Button::onMouseRelease);
}

void Button::setup()
{
	ofAddListener(ofEvents().mouseMoved, this, &Button::onMouseMove);
	ofAddListener(ofEvents().mousePressed, this, &Button::onMousePress);
	ofAddListener(ofEvents().mouseReleased, this, &Button::onMouseRelease);
}

void Button::setPosition(const ofVec2f& new_position)
{
	position_ = new_position;
}

const ofVec2f& Button::getPosition() const
{
	return position_;
}

void Button::setTitle(const std::string& new_title)
{
	title_ = new_title;
}

const std::string& Button::getTitle() const
{
	return title_;
}

ofEvent<const Button&>& Button::getEvent()
{
	return pressed_;
}

const ButtonPrototype& Button::getPrototype() const
{
	return base_;
}

ButtonPrototype::ButtonState Button::getState() const
{
	return state_;
}

void Button::onMouseMove(ofMouseEventArgs& parameter)
{
	if(contains(parameter) and state_ != ButtonPrototype::PRESSED)
		state_ = ButtonPrototype::ACTIVE;
	else
		state_ = ButtonPrototype::INACTIVE;
}

void Button::onMousePress(ofMouseEventArgs& parameter)
{
	if(state_ == ButtonPrototype::ACTIVE and parameter.button == OF_MOUSE_BUTTON_LEFT)
		state_ = ButtonPrototype::PRESSED;
}

void Button::onMouseRelease(ofMouseEventArgs& parameter)
{
	if(state_ == ButtonPrototype::PRESSED and parameter.button == OF_MOUSE_BUTTON_LEFT)
	{
		if(contains(parameter))
		{
			state_ = ButtonPrototype::ACTIVE;
			ofNotifyEvent(pressed_, *this, this);
			return;
		}
		state_ = ButtonPrototype::INACTIVE;
	}
}

bool Button::contains(const ofVec2f& point)
{
	const ofVec2f SIZE = base_.getSize();
	if(point.x < position_.x or point.x > position_.x + SIZE.x)
		return false;
	if(point.y < position_.y or point.y > position_.y + SIZE.y)
		return false;
	return true;
}
/*
void Button::draw() const
{
	base_->drawModel(*this);
}
*/


