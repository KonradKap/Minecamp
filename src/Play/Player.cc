/*
 * Player.cc
 *
 *  Created on: 30 maj 2016
 *      Author: konrad
 */

#include "Play/Player.h"

Player::Player() :
	position_(),
	direction_(),
	horizontal_angle_(),
	vertical_angle_()
{
	ofAddListener(ofEvents().update, this, &Player::onUpdate);
}

Player::~Player()
{
	ofRemoveListener(ofEvents().update, this, &Player::onUpdate);
}

double Player::getTop() const
{
	return getBottom() + HEIGHT;
}

double Player::getBottom() const
{
	return position_.y;
}

double Player::getLeft() const
{
	return position_.x + WIDTH;
}

double Player::getRight() const
{
	return position_.x - WIDTH;
}

double Player::getFront() const
{
	return position_.z + WIDTH;
}

double Player::getBack() const
{
	return position_.z - WIDTH;
}

vec3Dd Player::getEyePosition() const
{
	return position_ + vec3Dd(0.0, EYE_HEIGHT, 0.0);
}

void Player::setPosition(const vec3Dd& position)
{
	position_ = position;
}

void Player::applyDirection(const vec3Di& direction)
{
	direction_ = direction;
}

void Player::rotate(float horizontal_rotation, float vertical_rotation)
{
	horizontalRotate(horizontal_rotation);
	verticalRotate(vertical_rotation);
}

void Player::horizontalRotate(float rotation)
{
	horizontal_angle_ += rotation;
	while(horizontal_angle_ >= 180)
		horizontal_angle_ -= 360;
	while(horizontal_angle_ < -180)
		horizontal_angle_ += 360;
}

void Player::verticalRotate(float rotation)
{
	vertical_angle_ += rotation;
	if(vertical_angle_ > 90)
		vertical_angle_ = 90;
	else if(vertical_angle_ < -90)
		vertical_angle_ = -90;
}

float Player::getHorizontalAngle() const
{
	return horizontal_angle_/* +180*/;
}

float Player::getVerticalAngle() const
{
	return vertical_angle_ ;
}

ofEvent<WorldManager::blockEventArgs>& Player::getPlacedBlockEvent()
{
	return placedBlockEvent_;
}

ofEvent<vec3Di>& Player::getDestroyedBlockEvent()
{
	return destroyedBlockEvent_;
}

void Player::onUpdate(ofEventArgs& args)
{
	//std::cout << "POSITION: (" << position_.x << ", " << position_.y << ", " << position_.z << ")\n "
	//		<< "ANGLE: " << getHorizontalAngle() << ", " << getVerticalAngle() << std::endl;
	if(direction_ == vec3Di(0, 0, 0))
			return;
	double time = ofGetLastFrameTime();
	ofVec3f direction = ofVec3f(direction_);
	direction.rotate(vertical_angle_ , -View::xAxis())
			 .rotate(getHorizontalAngle(), View::yAxis());
	position_ += vec3Dd(direction*time*VELOCITY);
}


