/*
 * EquipmentManager.h
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */

#ifndef SRC_PLAY_EQUIPMENTMANAGER_H_
#define SRC_PLAY_EQUIPMENTMANAGER_H_

#include <functional>

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
	template<BlockType upper_limit, BlockType lower_limit>
		void makeStep(const std::function<int (int)>& step);

	BlockType currentBlock_;
};



#endif /* SRC_PLAY_EQUIPMENTMANAGER_H_ */
