/*
 * Player.cc
 *
 *  Created on: 30 maj 2016
 *      Author: konrad
 */

#include "Play/Player.h"

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

ofEvent<WorldManager::blockEventArgs>& Player::getPlacedBlockEvent()
{
	return placedBlockEvent_;
}

ofEvent<vec3Di>& Player::getDestroyedBlockEvent()
{
	return destroyedBlockEvent_;
}


