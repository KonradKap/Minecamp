/*
 * BlockModel.h
 *
 *  Created on: 12 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_WORLD_BLOCKMODEL_H_
#define SRC_GAME_WORLD_BLOCKMODEL_H_

#include <memory>

#include "BlockPathManager.h"

class BlockModel
{
public:
	BlockModel();
	BlockModel(const BlockType type);
	BlockModel(const BlockModel& bm);
	~BlockModel();

	bool isSolid() const;
	bool isLiquid() const;
private:
	enum BlockForm
	{
		SOLID, //Can mine it, can walk on it
		LIQUID, //Can swim, can't mine
		GAS, //Basically the air block
	};
	BlockForm form_;
	std::unique_ptr<ofTexture> side_texture_;
	std::unique_ptr<ofTexture> top_texture_;
	bool transparency_;

	ofFilePath ofp;
};



#endif /* SRC_GAME_WORLD_BLOCKMODEL_H_ */
