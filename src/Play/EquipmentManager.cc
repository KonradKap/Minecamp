/*
 * EquipmentManager.cc
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */


#include "EquipmentManager.h"

EquipmentManager::EquipmentManager() :
	currentBlock_(BlockType::DIRT)
{

}

EquipmentManager::~EquipmentManager()
{
}

void EquipmentManager::next()
{
	makeStep<BlockType::COUNT, BlockType::AIR>([](int a){return a + 1;});
}
void EquipmentManager::prev()
{
	makeStep<BlockType::AIR, BlockType::COUNT>([](int a){return a - 1;});
}

template<BlockType upper_limit, BlockType lower_limit>
	void EquipmentManager::makeStep(const std::function<int (int)>& step)
	{
		currentBlock_ = BlockType(step(int(currentBlock_)));
		if(currentBlock_ == upper_limit)
			currentBlock_ = BlockType(step(int(lower_limit)));
	}

BlockType EquipmentManager::getCurrentChoice() const
{
	return currentBlock_;
}
