/*
 * Button.cc
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#include "Menu/Button.h"
//#include "Utill/Registrable.h"

Button::Button(const ofVec2f& position, const std::string& title, const ButtonPrototype& base) :
	Registrable(),
	state_(ButtonPrototype::INACTIVE),
	position_(position),
	title_(title),
	base_(base)
{
	Registrable::registerMe();
}

Button::Button(const Button& b) :
	Registrable(),
	state_(b.state_),
	position_(b.position_),
	title_(b.title_),
	base_(b.base_)
{
	Registrable::registerMe();
}

Button::~Button()
{
	Registrable::unregisterMe();
}
/*
Button& Button::operator=(Button source)
{
	swap(*this, source);
	return *this;
}
*/
void Button::registerMe(const do_register_trait&)
{
	ofAddListener(ofEvents().mouseMoved, this, &Button::onMouseMove);
	ofAddListener(ofEvents().mousePressed, this, &Button::onMousePress);
	ofAddListener(ofEvents().mouseReleased, this, &Button::onMouseRelease);
}

void Button::unregisterMe(const do_register_trait&)
{
	ofRemoveListener(ofEvents().mouseMoved, this, &Button::onMouseMove);
	ofRemoveListener(ofEvents().mousePressed, this, &Button::onMousePress);
	ofRemoveListener(ofEvents().mouseReleased, this, &Button::onMouseRelease);
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
			Registrable::notify(pressed_, *this);
			//std::cout << "fired" << std::endl;
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
void swap(Button& first, Button& second)
{
	std::swap(first.position_, second.position_);
	std::swap(first.state_, second.state_);
	std::swap(first.title_, second.title_);
	//std::swap(first.base_, second.base_);
}
*/

