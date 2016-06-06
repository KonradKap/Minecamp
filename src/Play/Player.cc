/*
 * Player.cc
 *
 *  Created on: 30 maj 2016
 *      Author: konrad
 */

#include "Play/Player.h"

Player::Player() :
	Registrable(),
	position_(10,10,10),
	steer_(),
	horizontal_angle_(),
	vertical_angle_()
{
}

Player::~Player()
{
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
	return position_.y();
}

double Player::getLeft() const
{
	return position_.x() + WIDTH;
}

double Player::getRight() const
{
	return position_.x() - WIDTH;
}

double Player::getFront() const
{
	return position_.z() + WIDTH;
}

double Player::getBack() const
{
	return position_.z() - WIDTH;
}

double Player::getHeight() const
{
	return HEIGHT;
}

double Player::getWidth() const
{
	return WIDTH;
}



vec3Dd Player::getEyePosition() const
{
	return position_ + vec3Dd(0.0, EYE_HEIGHT, 0.0);
}

vec3Dd Player::getPosition() const
{
	return position_;
}

void Player::setPosition(const vec3Dd& position)
{
	position_ = position;
}

void Player::setGround(bool state)
{
	on_the_ground_=state;
}

vec3Dd Player::getDirectionVector() const
{
	return vec3Dd( ofVec3f(0, 0, 1).rotate(getVerticalAngle() , -View::xAxis())
			 	 	  .rotate(getHorizontalAngle(), View::yAxis()));
}

vec3Dd Player::getMovingDirectionVector() const
{
	return vec3Dd(ofVec3f(steer_).rotate(getHorizontalAngle(), View::yAxis()));
}

void Player::setSteer(const vec3Di& steering)
{
	steer_ = steering;
}
vec3Di Player::getSteer() const
{
	return steer_;
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

void Player::setYVelocity(const double yVelocity)
{
	y_velocity_=yVelocity;
}
void Player::onUpdate(ofEventArgs& args)
{
	if(steer_ == vec3Di(0, 0, 0))
			return;
}



void Player::moveUpdate()
{
			double dtime = ofGetLastFrameTime();
	        double distance = dtime * VELOCITY;

	        vec3Dd direction = getMovingDirectionVector();

	        direction*= distance;

	        y_velocity_ -= dtime * GRAVITY;
	        y_velocity_ = (y_velocity_<-TVELOCITY) ?  -TVELOCITY : y_velocity_;
	        direction.y()+=y_velocity_*dtime;
	        position_+= direction ;

}

void Player::jumpPlayer()
{
	if(on_the_ground_)
	{
		setYVelocity(JUMPSPEED);
		on_the_ground_=false;
	}
}






