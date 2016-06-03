/*
 * EquipmentManager.h
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */

#ifndef SRC_PLAY_EQUIPMENTMANAGER_H_
#define SRC_PLAY_EQUIPMENTMANAGER_H_

#include "World/BlockType.h"

class EquipmentManager
{
public:
	EquipmentManager();
	~EquipmentManager();

	void next();
	void prev();
	BlockType getCurrentChoice() const;
private:

	BlockType currentBlock_;
};



#endif /* SRC_PLAY_EQUIPMENTMANAGER_H_ */
