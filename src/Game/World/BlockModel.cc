/*
 * BlockModel.cc
 *
 *  Created on: 17 mar 2016
 *      Author: konrad
 */

#include "Game/World/BlockModel.h"

BlockModel::BlockModel() :
	type_(BlockType::COUNT),
	form_(BlockForm::GAS),
	image_(),
	transparency_(true)
{
}

BlockModel::BlockModel(const BlockType type, const std::string& path) :
	type_(type),
	form_(),
	image_(path),
	transparency_()
{
	switch(type_)
	{
	case BlockType::AIR:
		form_ = GAS;
		transparency_ = true;
		break;
	case BlockType::DIRT:
	case BlockType::STONE:
		form_ = SOLID;
		transparency_ = false;
		break;
	case BlockType::FIRE:
	case BlockType::WATER:
		form_ = LIQUID;
		transparency_ = true;
		break;
	default:
		throw std::invalid_argument("There was no block of this type defined");
	}
}

BlockModel::BlockModel(const BlockModel& bm) :
	type_(bm.type_),
	form_(bm.form_),
	image_(bm.image_),
	transparency_(bm.transparency_)
{
}

BlockModel::~BlockModel()
{
}

bool BlockModel::isSolid() const
{
	return form_ == SOLID;
}

bool BlockModel::isLiquid() const
{
	return form_ == LIQUID;
}

bool BlockModel::isGas() const
{
	return form_ == GAS;
}

bool BlockModel::isTransparent() const
{
	return transparency_;
}

ofTexture& BlockModel::getTexture()
{
	return image_.getTexture();
}

const ofTexture& BlockModel::getTexture() const
{
	return image_.getTexture();
}

BlockType BlockModel::getType() const
{
	return type_;
}
