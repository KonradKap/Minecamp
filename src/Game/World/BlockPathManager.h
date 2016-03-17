/*
 * BlockPathManager.h
 *
 *  Created on: 17 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_WORLD_BLOCKPATHMANAGER_H_
#define SRC_GAME_WORLD_BLOCKPATHMANAGER_H_

#include "PathManager.h"

enum class BlockType
{
	AIR,
	DIRT,
	STONE,
	WATER,
	FIRE,
	COUNT
};

class BlockPathManager : public PathManager<BlockType>
{
public:
	BlockPathManager() :
		PathManager<BlockType>(std::map<const BlockType, const std::string>(
				{
					{BlockType::AIR, block("null.png")},
					{BlockType::DIRT, block("dirt.png")},
					{BlockType::STONE, block("stone.png")},
					{BlockType::WATER, block("water.png")},
					{BlockType::FIRE, block("fire.png")},
				}
		))
	{
	}

	~BlockPathManager() {}
};



#endif /* SRC_GAME_WORLD_BLOCKPATHMANAGER_H_ */
