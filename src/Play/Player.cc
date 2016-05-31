/*
 * Player.cc
 *
 *  Created on: 30 maj 2016
 *      Author: konrad
 */

#include "Play/Player.h"

ofEvent<WorldManager::blockEventArgs>& Player::getPlacedBlockEvent()
{

	return placedBlockEvent_;
}

ofEvent<vec3Di>& Player::getDestroyedBlockEvent()
{
	return destroyedBlockEvent_;
}


