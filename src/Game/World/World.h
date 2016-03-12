/*
 * World.h
 *
 *  Created on: 12 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_WORLD_H_
#define SRC_GAME_WORLD_H_

#include <array>

class BlockModel;

class World
{
public:
	static const int X_SIZE = 256;
	static const int Y_SIZE = 256;
	static const int Z_SIZE = 256;
private:
	typedef std::array< std::array < std::array <const BlockModel*, Z_SIZE>, Y_SIZE>, X_SIZE> Map3d;
	//std::map<int, BlockModel> dictionary_;
	Map3d map_;
};



#endif /* SRC_GAME_WORLD_H_ */
