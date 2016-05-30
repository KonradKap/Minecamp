/*
 * World.h
 *
 *  Created on: 30 maj 2016
 *      Author: konrad
 */

#ifndef SRC_WORLD_WORLD_H_
#define SRC_WORLD_WORLD_H_

#include "ofEvents.h"

#include "World/WorldManager.h"
#include "Play/Player.h"

class World
{
public:
	World();

private:
	WorldManager manager_;
	Player player_;
};



#endif /* SRC_WORLD_WORLD_H_ */
