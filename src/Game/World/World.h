/*
 * World.h
 *
 *  Created on: 12 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_WORLD_H_
#define SRC_GAME_WORLD_H_

#include <array>
#include <fstream>
#include <cassert>
#include <iostream>

#include "Utill/Trio.h"
#include "ofVbo.h"
#include "ofVboMesh.h"
#include "of3dPrimitives.h"
#include "ofGraphics.h"

#include "Game/World/BlockModel.h"


//TODO: Make all of the fun(int x, int y, int z) use triple instead
class World
{
public:
	World();
	World(const World& w) = delete;
	~World();

	void setup();

	void loadFromFile(std::ifstream& file);
	void saveToFile(std::ofstream& file);

	void draw() const;

	void onBlockDestruction(const trio_i& position);
	void onBlockPlacement(const trio_i& position, BlockType type);

	static const int X_SIZE = 256;
	static const int Y_SIZE = 256;
	static const int Z_SIZE = 256;
	static const int CHUNK_SIZE = 16;
private:
	bool isVisible(const trio_i& position, Side side) const;
	void setupBuffer();
	void addToMesh(const trio_i& position, const std::array<ofVec3f, 6>& shift);
	const BlockModel& getBlock(const trio_i& position) const;
	BlockModel& getBlock(const trio_i& position);
	const ofMesh& getBuffer(const trio_i& position, BlockType type) const;
	ofMesh& getBuffer(const trio_i& position, BlockType type);

	typedef std::array< std::array < std::array <BlockModel*, Z_SIZE>, Y_SIZE>, X_SIZE> map_t;
	map_t map_;

	std::array<BlockModel, size_t(BlockType::COUNT)> models_;

	typedef std::array< std::array< std::array <std::array <ofMesh, size_t(BlockType::COUNT)>, Z_SIZE/CHUNK_SIZE>, Y_SIZE/CHUNK_SIZE>, X_SIZE/CHUNK_SIZE> buffer_t;
	buffer_t buffer_;
};



#endif /* SRC_GAME_WORLD_H_ */
