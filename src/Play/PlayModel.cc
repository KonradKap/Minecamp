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
	player_.moveUpdate();

	player_.setPosition(collide(player_.getPosition()));




}

Player& PlayModel::getPlayer()
{
	return const_cast<Player&>(static_cast<const PlayModel*>(this)->getPlayer());
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
	return const_cast<WorldManager&>(static_cast<const PlayModel*>(this)->getWorldManager());
}

const BufferManager& PlayModel::getBufferManager() const
{
	return buffer_manager_;
}

EquipmentManager& PlayModel::getEquipmentManager()
{
	return const_cast<EquipmentManager&>(static_cast<const PlayModel*>(this)->getEquipmentManager());
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
	const double pad = 0.25* BlockPrototype::SIZE;
	for (int i =0 ; i<3;++i)
	{
		normalize[i]-=normalize[i]%16;
	}




	for( unsigned i = 0; i< unsigned(Side::COUNT) ;++i)
	{
		vec3Dd face = vec3Dd(vec3Di::make_unit_vector(Side(i)));
		double d=0;

		cout << position.x()<<" "<< position.y() <<" "<< position.z()<< endl;
		for(int j=0;j<3;j++)
		{
			if (face[j]==0)
			{
				continue;
			}
			cout <<endl;

			cout << position[j] << " "<< normalize[j]<< endl;
			cout <<endl;
			d = (position[j]-normalize[j])*face[j];
			d*=1;


			if (d<pad)
			{
				cout<< d << " "<< pad << endl;
				cout << "if 2"<< endl;
				continue;

			}
			vec3Di op = normalize;

			for(int dy= 0 ; dy <=player_.getHeight()/16; ++dy)
			{
				op[1] += dy;
				op[j] += face[j];

				cout << op.x()<<" "<< op.y() <<" "<< op.z()<< endl;
				cout << "befor colision"<< endl;
				//if((!world_manager_.isWithin(op))) continue;
				//if (!world_manager_.getBlock(op).isSolid() and (!world_manager_.isWithin(op))) continue;

				//if (world_manager_.isWithin(op/BlockPrototype::SIZE)) continue;
				if (!world_manager_.getBlock(op/BlockPrototype::SIZE).isSolid() and world_manager_.isWithin(op/BlockPrototype::SIZE)) continue;


				position[j] -= (d -pad) * face[j];
				cout<< "colision"<<endl;
				if (Side(i) == Side::BOTTOM or Side(i) == Side::TOP) player_.setYVelocity(0);

				break;
			}
		}
	}
	//cout << position.x<< position.y << position.z<< endl;
	cout<< "return position"<<endl;
	cout << position.x()<<" "<< position.y()<<" " << position.z()<<" "<< endl;

	return position;
}



