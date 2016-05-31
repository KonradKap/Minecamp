/*
 * Player.h
 *
 *  Created on: 30 maj 2016
 *      Author: konrad
 */

#ifndef SRC_PLAY_PLAYER_H_
#define SRC_PLAY_PLAYER_H_

#include "ofEvent.h"

#include "World/WorldManager.h"

class Player
{
public:


	ofEvent<WorldManager::blockEventArgs>& getPlacedBlockEvent();
	ofEvent<vec3Di>& getDestroyedBlockEvent();
private:
	ofEvent<WorldManager::blockEventArgs> placedBlockEvent_;
	ofEvent<vec3Di> destroyedBlockEvent_;
};




#endif /* SRC_PLAY_PLAYER_H_ */
