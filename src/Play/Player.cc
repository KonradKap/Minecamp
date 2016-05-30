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

ofEvent<WorldManager::blockEventArgs>& Player::getDestroyedBlockEvent()
{
	return destroyedBlockEvent_;
}


