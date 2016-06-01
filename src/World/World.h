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
#include "World/SaveFileManager.h"
#include "Play/Player.h"

class World
{
public:
	World(int save_state);

	~World();

	const WorldManager& getWorldManager() const;
	const Player& getPlayer() const;
private:


	WorldManager world_manager_;
	SaveFileManager save_file_manager_;
	Player player_;
};



#endif /* SRC_WORLD_WORLD_H_ */
