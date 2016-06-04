/*
 * Player.cc
 *
 *  Created on: 30 maj 2016
 *      Author: konrad
 */

#include "Play/Player.h"

Player::Player() :
	position_(),
	//direction_(1, 0, 0),
	steer_(),
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

vec3Dd Player::getDirectionVector(ofVec3f base) const
{
	//ofVec3f direction(0, 0, 1);
	return vec3Dd(base.rotate(getVerticalAngle() , -View::xAxis())
			 	 	  .rotate(getHorizontalAngle(), View::yAxis()));

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
	//direction_ = ofVec3f(direction_).rotate(rotationAngle, View::yAxis());
	horizontal_angle_ += rotationAngle;
	while(horizontal_angle_ >= 180)
		horizontal_angle_ -= 360;
	while(horizontal_angle_ < -180)
		horizontal_angle_ += 360;

}

void Player::verticalRotate(float rotationAngle)
{
	//direction_ = ofVec3f(direction_).rotate(rotationAngle, View::xAxis());
	vertical_angle_ += rotationAngle;
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

/*void setYVelocity(const double yValue)
{
	yVelocity=yValue;
}*/

void Player::onUpdate(ofEventArgs& args)
{
	//std::cout << "POSITION: (" << position_.x << ", " << position_.y << ", " << position_.z << ")\n "
	//		<< "ANGLE: " << getHorizontalAngle() << ", " << getVerticalAngle() << std::endl;
	if(steer_ == vec3Di(0, 0, 0))
			return;
	double time = ofGetLastFrameTime();
/*
	vec3Dd distance = direction_*time*VELOCITY;
	distance.x *= steer_.x;
	distance.y *= steer_.y;
	distance.z *= steer_.z;
*/

	//ofVec3f direction = ofVec3f(steer_);
	//direction.rotate(getVerticalAngle() , -View::xAxis())
	//		 .rotate(getHorizontalAngle(), View::yAxis());
	//vec3Dd distance = vec3Dd(getDirectionVector(ofVec3f(steer_))*time*VELOCITY);
	position_ += moveUpdate(steer_,time);
	//position_ += distance;
}


vec3Dd Player::moveUpdate(vec3Di steer, double dtime)
{

	        double distance = dtime * VELOCITY;
	        vec3Dd direction = getDirectionVector(ofVec3f(steer));


	        direction*= distance;


	        yVelocity -= dtime * GRAVITY;

	        yVelocity = (yVelocity<VELOCITY) ?  VELOCITY : yVelocity;
	        yVelocity += yVelocity * dtime;
	        //collisions
	        vec3Dd position = position_;
	        //position = collide(position+direction);
	        position+=direction;

	        return direction;


}

/*vec3Dd Player::collide(vec3Dd position){

	vec3Dd normalize = position;
	double pad = 0.25;





	for( int enumI= Side::FRONT; enumI!=Side::COUNT;++enumI)
	{
		vec3Dd face = vec3Dd::make_unit_vector(static_cast<Side>(enumI));
		double d=0;

		for(int j=0;j<3;j++)
		{
			if (!face[j]) continue;
			d = (position[j]- (int)normalize[j])*face[j];

			if (d<pad) continue;
			vec3Dd op = normalize;

			for(int dy= 0 ; dy <=HEIGHT/16; ++dy)
			{
				op[1] -= dy;
				op[j] += face[j];
				if (PlayModel::getWorldManager()getBlock(op).isSolid()) continue;

				position[j] -= (d - pad) * face[j];
				if (enumI == Side::BOTTOM or enumI == Side::TOP)
				{
				 yVelocity=0;

				}
				break;
			}
		}
	return position;

	}
}*/




