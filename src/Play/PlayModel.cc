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
	save_file_manager_(save_state, *this),
	equipment_manager_(),
	player_()
{
	save_file_manager_.load();
	buffer_manager_.setup();
}

PlayModel::~PlayModel()
{
	//save_file_manager_.save();
}

void PlayModel::registerMe(const do_register_trait&)
{
	ofAddListener(ofEvents().update, this, &PlayModel::onUpdate);
	world_manager_.Registrable::registerMe();
	buffer_manager_.Registrable::registerMe();
	player_.Registrable::registerMe();
}

void PlayModel::unregisterMe(const do_register_trait&)
{
	ofRemoveListener(ofEvents().update, this, &PlayModel::onUpdate);
	world_manager_.Registrable::unregisterMe();
	buffer_manager_.Registrable::unregisterMe();
	player_.Registrable::unregisterMe();
}

void PlayModel::onUpdate(ofEventArgs&)
{

	player_.setPosition(collide(player_.getPosition()));




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

void PlayModel::save() const
{
	save_file_manager_.save();
}

void PlayModel::load()
{
	save_file_manager_.load();
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


vec3Dd PlayModel::collide(vec3Dd position)
{

	vec3Di normalize = vec3Di(position);
	double pad = 0.25;




	for( unsigned i = 0; i< unsigned(Side::COUNT) ;++i)
	{
		vec3Dd face = vec3Dd(vec3Di::make_unit_vector(Side(i)));
		double d=0;

		for(int j=0;j<3;j++)
		{
			if (!face[j]) continue;
			d = (position[j]-normalize[j])*face[j];

			if (d<pad) continue;
			vec3Di op = normalize;

			for(int dy= 0 ; dy <=player_.getHeight()/16; ++dy)
			{
				op[1] -= dy;
				op[j] += face[j];
				//if (world_manager_.isWithin(op)) continue;
				if (!world_manager_.getBlock(op).isSolid()) continue;

				position[j] -= (d - pad) * face[j];
				if (Side(i) == Side::BOTTOM or Side(i) == Side::TOP) player_.setYVelocity(0);

				break;
			}
		}
	}
	return position;
}



