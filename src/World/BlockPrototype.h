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

class BlockPrototype
{
public:
	BlockPrototype();
	BlockPrototype(const BlockType type, const std::string& path);
	BlockPrototype(const BlockPrototype& bm);
	~BlockPrototype();

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
		GAS, //Can't mine, can walk through
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
