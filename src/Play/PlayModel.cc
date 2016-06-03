/*
 * Play.cc
 *
 *  Created on: 12 mar 2016
 *      Author: konrad
 */

#include "PlayModel.h"

PlayModel::PlayModel(int save_state) :
	Model(),
	world_manager_(),
	buffer_manager_(world_manager_),
	save_file_manager_(save_state, world_manager_),
	equipment_manager_(),
	player_()
{
	save_file_manager_.load();
	buffer_manager_.setup();

}

PlayModel::~PlayModel()
{
	save_file_manager_.save();
}

Player& PlayModel::getPlayer()
{
	return player_;
}

const Player& PlayModel::getPlayer() const
{
	return player_;
}

const WorldManager& PlayModel::getWorldManager() const
{
	return world_manager_;
}

WorldManager& PlayModel::getWorldManager()
{
	return world_manager_;
}

const BufferManager& PlayModel::getBufferManager() const
{
	return buffer_manager_;
}

EquipmentManager& PlayModel::getEquipmentManager()
{
	return equipment_manager_;
}

const EquipmentManager& PlayModel::getEquipmentManager() const
{
	return equipment_manager_;
}

std::pair<vec3Di, vec3Di> PlayModel::findTargetedBlock() const
{
	const int RESOLUTION = 8;
	vec3Dd ray_walker = player_.getEyePosition();
	vec3Dd step = player_.getDirectionVector()/RESOLUTION;

	vec3Di previous;

	for(int i = 0; i < RESOLUTION*Player::RANGE; ++i)
	{
		vec3Di current = vec3Di(ray_walker)/BlockPrototype::SIZE;
		if(!world_manager_.isWithin(current))
			break;

		if (current != previous and world_manager_.getBlock(current).isSolid())
				return std::make_pair(current, previous);
		previous = current;
		ray_walker += step;
	}
	return std::make_pair(vec3Di(-1,-1,-1), vec3Di(-1,-1,-1));
}



