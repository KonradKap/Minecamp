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
	currentBlock_ = BlockType(int(currentBlock_) + 1);
	if(currentBlock_ == BlockType::COUNT)
		currentBlock_ = BlockType(int(BlockType::AIR) + 1);
	//currentBlock_ = BlockType(((int(currentBlock_)+1)%int(BlockType::COUNT))+1);
}
void EquipmentManager::prev()
{
	currentBlock_ = BlockType(int(currentBlock_) - 1);
	if(currentBlock_ == BlockType::AIR)
		currentBlock_ = BlockType(int(BlockType::COUNT) - 1);
}

BlockType EquipmentManager::getCurrentChoice() const
{
	return currentBlock_;
}
