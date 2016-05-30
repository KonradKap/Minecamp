/*
 * World.cc
 *
 *  Created on: 30 maj 2016
 *      Author: konrad
 */

#include "World/World.h"

World::World() :
	manager_(),
	player_()
{
	manager_.registerListeners(player_);
	//ofAddListener(player_.getDestroyedBlockEvent(), &manager_, &WorldManager::onBlockDestruction);
	//ofAddListener(player_.getPlacedBlockEvent(), &manager_, &WorldManager::onBlockPlacement);

}

