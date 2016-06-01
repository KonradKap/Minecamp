/*
 * Side.h
 *
 *  Created on: 25 mar 2016
 *      Author: konrad
 */

#ifndef SRC_UTILL_SIDE_H_
#define SRC_UTILL_SIDE_H_

#include "../World/BlockPrototype.h"

enum class Side
{
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	COUNT
};
/** TEMPORARY, REALLY NEED TO FIND PLACE FOR THEM */

const std::array<ofVec3f, 8> VERTICES =
{
	ofVec3f(0, 			   	  0, 				0				),
	ofVec3f(BlockPrototype::SIZE, 0, 				0				),
	ofVec3f(0, 			      BlockPrototype::SIZE, 0			 	),
	ofVec3f(0, 			      0, 				BlockPrototype::SIZE),
	ofVec3f(BlockPrototype::SIZE, BlockPrototype::SIZE, 0				),
	ofVec3f(BlockPrototype::SIZE, 0, 				BlockPrototype::SIZE),
	ofVec3f(0, 			      BlockPrototype::SIZE, BlockPrototype::SIZE),
	ofVec3f(BlockPrototype::SIZE, BlockPrototype::SIZE, BlockPrototype::SIZE)
};

const std::array<std::array<ofVec3f, 6>, unsigned(Side::COUNT)> SIDE_VERTICES =
{
	std::array<ofVec3f, 6>({VERTICES[3], VERTICES[5], VERTICES[7], VERTICES[3], VERTICES[6], VERTICES[7]}),
	std::array<ofVec3f, 6>({VERTICES[0], VERTICES[1], VERTICES[4], VERTICES[0], VERTICES[2], VERTICES[4]}),
	std::array<ofVec3f, 6>({VERTICES[0], VERTICES[3], VERTICES[6], VERTICES[0], VERTICES[2], VERTICES[6]}),
	std::array<ofVec3f, 6>({VERTICES[1], VERTICES[4], VERTICES[7], VERTICES[1], VERTICES[5], VERTICES[7]}),
	std::array<ofVec3f, 6>({VERTICES[0], VERTICES[1], VERTICES[5], VERTICES[0], VERTICES[3], VERTICES[5]}),
	std::array<ofVec3f, 6>({VERTICES[2], VERTICES[4], VERTICES[7], VERTICES[2], VERTICES[6], VERTICES[7]}),
};



#endif /* SRC_UTILL_SIDE_H_ */
