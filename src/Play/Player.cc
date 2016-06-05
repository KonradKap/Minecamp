/*
 * Player.cc
 *
 *  Created on: 30 maj 2016
 *      Author: konrad
 */

#include "Play/Player.h"

Player::Player() :
	Registrable(),
	position_(5*16,11*16+1,5*16),
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

int Player::getHeight() const
{
	return HEIGHT;
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

vec3Dd Player::getDirectionVector(ofVec3f base) const
{
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
	//double time = ofGetLastFrameTime();

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
	//position_ += moveUpdate();
	//position_ += distance;
}



void Player::moveUpdate()

//TODO: Znormalizować steer_, tak, zeby poruszanie na skos ('w' i 'a', dla przykladu)
//		bylo tak samo szybkie jak poruszanie sie prosto
//		dla wcisnietych 'w' i 'a' dlugosc steer_ ~= 1.41, natomiast dla samego w == 1




{
			double dtime = ofGetLastFrameTime();
	        double distance = dtime * VELOCITY;
	        vec3Dd direction = getDirectionVector(ofVec3f(steer_));


	        direction*= distance;


	        /*y_velocity_ -= dtime * GRAVITY;

	        y_velocity_ = (y_velocity_<VELOCITY) ?  VELOCITY : y_velocity_;
	        y_velocity_ += y_velocity_ * dtime;*/

	        position_+= direction ;


	        //return direction;




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




