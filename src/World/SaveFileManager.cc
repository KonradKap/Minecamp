/*
 * SaveFileManager.cc
 *
 *  Created on: 31 maj 2016
 *      Author: konrad
 */

#include "World/SaveFileManager.h"

SaveFileManager::SaveFileManager(int save_state, WorldManager& world_manager) :
	save_state_(save_state),
	world_manager_(world_manager)
{

}

void SaveFileManager::load()
{
	std::ifstream file(getSaveFileName(save_state_));
	if(!file.is_open())
		world_manager_.loadDefaultWorld();
	else
		world_manager_.loadFromFile(file);
	file.close();
}

void SaveFileManager::save()
{
	std::ofstream file(getSaveFileName(save_state_));
	if(!file.is_open())
		throw std::ios_base::failure("Unable to open file");

	world_manager_.saveToFile(file);
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

