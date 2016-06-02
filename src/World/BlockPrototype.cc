/*
 * BlockModel.cc
 *
 *  Created on: 17 mar 2016
 *      Author: konrad
 */

#include "BlockPrototype.h"

BlockPrototype::BlockPrototype() :
	type_(BlockType::COUNT),
	form_(BlockForm::GAS),
	image_(),
	transparency_(true)
{
}

BlockPrototype::BlockPrototype(const BlockType type, const std::string& path) :
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

BlockPrototype::BlockPrototype(const BlockPrototype& bm) :
	type_(bm.type_),
	form_(bm.form_),
	image_(bm.image_),
	transparency_(bm.transparency_)
{
}

BlockPrototype::~BlockPrototype()
{
}

bool BlockPrototype::isSolid() const
{
	//if(form_ == SOLID) std::cout << "solid " << std::endl;
	//else std::cout << "nosolid " << std::endl;
	return form_ == SOLID;
}

bool BlockPrototype::isLiquid() const
{
	return form_ == LIQUID;
}

bool BlockPrototype::isGas() const
{
	return form_ == GAS;
}

bool BlockPrototype::isTransparent() const
{
	return transparency_;
}

ofImage& BlockPrototype::getTexture()
{
	return image_;
}

const ofImage& BlockPrototype::getTexture() const
{
	return image_;
}

BlockType BlockPrototype::getType() const
{
	return type_;
}

