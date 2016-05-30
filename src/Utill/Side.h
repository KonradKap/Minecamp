/*
 * Side.h
 *
 *  Created on: 25 mar 2016
 *      Author: konrad
 */

#ifndef SRC_UTILL_SIDE_H_
#define SRC_UTILL_SIDE_H_

#include "BlockModel.h"

enum class Side
{
	FRONT,
	BACK,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	COUNT
};
/** TEMPORARY, REALLY NEED TO FIND PLACE FOR THEM */

const std::array<ofVec3f, 8> VERTICES =
{
	ofVec3f(0, 			   	  0, 				0				),
	ofVec3f(BlockModel::SIZE, 0, 				0				),
	ofVec3f(0, 			      BlockModel::SIZE, 0			 	),
	ofVec3f(0, 			      0, 				BlockModel::SIZE),
	ofVec3f(BlockModel::SIZE, BlockModel::SIZE, 0				),
	ofVec3f(BlockModel::SIZE, 0, 				BlockModel::SIZE),
	ofVec3f(0, 			      BlockModel::SIZE, BlockModel::SIZE),
	ofVec3f(BlockModel::SIZE, BlockModel::SIZE, BlockModel::SIZE)
};

const std::array<std::array<ofVec3f, 6>, unsigned(Side::COUNT)> SIDE_VERTICES =
{
	std::array<ofVec3f, 6>({VERTICES[3], VERTICES[5], VERTICES[7], VERTICES[3], VERTICES[6], VERTICES[7]}),
	std::array<ofVec3f, 6>({VERTICES[0], VERTICES[1], VERTICES[4], VERTICES[0], VERTICES[2], VERTICES[4]}),
	std::array<ofVec3f, 6>({VERTICES[0], VERTICES[1], VERTICES[5], VERTICES[0], VERTICES[3], VERTICES[5]}),
	std::array<ofVec3f, 6>({VERTICES[2], VERTICES[4], VERTICES[7], VERTICES[2], VERTICES[6], VERTICES[7]}),
	std::array<ofVec3f, 6>({VERTICES[0], VERTICES[3], VERTICES[6], VERTICES[0], VERTICES[2], VERTICES[6]}),
	std::array<ofVec3f, 6>({VERTICES[1], VERTICES[4], VERTICES[7], VERTICES[1], VERTICES[5], VERTICES[7]})
};



#endif /* SRC_UTILL_SIDE_H_ */
