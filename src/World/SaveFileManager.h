/*
 * SaveFileManager.h
 *
 *  Created on: 31 maj 2016
 *      Author: konrad
 */

#ifndef SRC_WORLD_SAVEFILEMANAGER_H_
#define SRC_WORLD_SAVEFILEMANAGER_H_

#include "World/WorldManager.h"

class SaveFileManager
{
public:
	SaveFileManager(int save_state, WorldManager& world_manager);

	void load();
	void save();
	static bool clear(int save_state);

private:
	static std::string getSaveFileName(int save_state);

	int save_state_;
	WorldManager& world_manager_;

};




#endif /* SRC_WORLD_SAVEFILEMANAGER_H_ */
