/*
 * BlockModel.h
 *
 *  Created on: 12 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_WORLD_BLOCKMODEL_H_
#define SRC_GAME_WORLD_BLOCKMODEL_H_

#include <memory>

#include "ofImage.h"

#include "World/BlockPathManager.h"

class BlockModel
{
public:
	BlockModel();
	BlockModel(const BlockType type, const std::string& path);
	BlockModel(const BlockModel& bm);
	~BlockModel();

	bool isSolid() const;
	bool isLiquid() const;
	bool isGas() const;
	bool isTransparent() const;

	ofImage& getTexture();
	const ofImage& getTexture() const;

	BlockType getType() const;

	static const int SIZE = 16;
private:
	enum BlockForm
	{
		SOLID, //Can mine it, can walk on it
		LIQUID, //Can swim, can't mine
		GAS, //Basically the air block
	};
	BlockType type_;
	BlockForm form_;
	ofImage image_;
	bool transparency_;
};
/*
bool operator< (const BlockModel& arg1, const BlockModel& arg2)
{
	return false;
}
*/

#endif /* SRC_GAME_WORLD_BLOCKMODEL_H_ */
