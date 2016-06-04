/*
 * SaveFileManager.cc
 *
 *  Created on: 31 maj 2016
 *      Author: konrad
 */

#include "Play/SaveFileManager.h"
#include "Play/PlayModel.h"

SaveFileManager::SaveFileManager(int save_state, PlayModel& source) :
	save_state_(save_state),
	source_(source)
{

}

void SaveFileManager::load()
{
	std::ifstream file(getSaveFileName(save_state_));
	if(!file.is_open())
		source_.getWorldManager().loadDefaultWorld();
	else
	{
		source_.getWorldManager().loadFromFile(file);
		loadPlayer(file);
	}
	file.close();
}

void SaveFileManager::save() const
{
	std::ofstream file(getSaveFileName(save_state_));
	if(!file.is_open())
		throw std::ios_base::failure("Unable to open file");

	source_.getWorldManager().saveToFile(file);
	savePlayer(file);
	file.close();
}

bool SaveFileManager::clear(int save_state)
{
	return std::remove(getSaveFileName(save_state).c_str()) == 0;
}

std::string SaveFileManager::getSaveFileName(int save_state)
{
	return std::to_string(save_state)+"_"
		   +std::to_string(WorldManager::X_SIZE)+"_"
		   +std::to_string(WorldManager::Y_SIZE)+"_"
		   +std::to_string(WorldManager::Z_SIZE)+".sav";
}

void SaveFileManager::loadPlayer(std::istream& file)
{
	loadPlayerPosition(file);
	loadPlayerDirection(file);
}

void SaveFileManager::loadPlayerPosition(std::istream& file)
{
	vec3Dd position;
	file >> position.x();
	file >> position.y();
	file >> position.z();
	source_.getPlayer().setPosition(position);
}

void SaveFileManager::loadPlayerDirection(std::istream& file)
{
	float angle;
	file >> angle;
	source_.getPlayer().verticalRotate(angle);
	file >> angle;
	source_.getPlayer().horizontalRotate(angle);
}

void SaveFileManager::savePlayer(std::ostream& file) const
{
	file << source_.getPlayer().getPosition().x() << " ";
	file << source_.getPlayer().getPosition().y() << " ";
	file << source_.getPlayer().getPosition().z() << " ";
	file << source_.getPlayer().getVerticalAngle() << " ";
	file << source_.getPlayer().getHorizontalAngle() << " ";
}
