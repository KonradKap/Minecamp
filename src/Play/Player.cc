/*
 * Player.cc
 *
 *  Created on: 30 maj 2016
 *      Author: konrad
 */

#include "Play/Player.h"

Player::Player() :
	Registrable(),
	position_(),
	steer_(),
	horizontal_angle_(),
	vertical_angle_()
{
	Registrable::registerMe();
}

Player::~Player()
{
	Registrable::unregisterMe();
}

void Player::registerMe(const do_register_trait&)
{
	ofAddListener(ofEvents().update, this, &Player::onUpdate);
}

void Player::unregisterMe(const do_register_trait&)
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

vec3Dd Player::getDirectionVector(ofVec3f base) const
{
	return vec3Dd(base.rotate(getVerticalAngle() , -View::xAxis())
			 	 	  .rotate(getHorizontalAngle(), View::yAxis()));
}

void Player::setSteer(const vec3Di& steering)
{
	steer_ = steering;
}

void Player::rotate(float horizontal_rotation, float vertical_rotation)
{
	horizontalRotate(horizontal_rotation);
	verticalRotate(vertical_rotation);
}

void Player::horizontalRotate(float rotationAngle)
{
	horizontal_angle_ += rotationAngle;
	while(horizontal_angle_ >= 180)
		horizontal_angle_ -= 360;
	while(horizontal_angle_ < -180)
		horizontal_angle_ += 360;
}

void Player::verticalRotate(float rotationAngle)
{
	vertical_angle_ += rotationAngle;
	if(vertical_angle_ > 90)
	vertical_angle_ = 90;
	else if(vertical_angle_ < -90)
		vertical_angle_ = -90;
}

float Player::getHorizontalAngle() const
{
	return horizontal_angle_;
}

float Player::getVerticalAngle() const
{
	return vertical_angle_ ;
}

void Player::onUpdate(ofEventArgs& args)
{
	if(steer_ == vec3Di(0, 0, 0))
			return;
	double time = ofGetLastFrameTime();
	vec3Dd distance = vec3Dd(getDirectionVector(ofVec3f(steer_))*time*VELOCITY);
	position_ += distance;
}


