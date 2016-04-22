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


class World
{
public:
	static const int X_SIZE = 16;
	static const int Y_SIZE = 16;
	static const int Z_SIZE = 16;
	static const int CHUNK_SIZE = 16;

	typedef std::array< std::array < std::array <BlockModel*, Z_SIZE>, Y_SIZE>, X_SIZE> map_t;
	typedef std::array< std::array< std::array <std::array <ofMesh, size_t(BlockType::COUNT)>, Z_SIZE/CHUNK_SIZE>, Y_SIZE/CHUNK_SIZE>, X_SIZE/CHUNK_SIZE> buffer_t;

	World();
	World(const World& w) = delete;
	~World();

	void setup();

	void loadFromFile(std::ifstream& file);
	void saveToFile(std::ofstream& file);

//	void draw() const;

	void onBlockDestruction(const trio_i& position);
	void onBlockPlacement(const trio_i& position, BlockType type);

	const BlockModel& getBlock(const trio_i& position) const;

	const buffer_t& getBuffer() const;
	const ofMesh& getBuffer(const trio_i& position, BlockType type) const;

	const BlockModel& getModel(const BlockType type) const;
private:
	bool isVisible(const trio_i& position, Side side) const;
	void setupBuffer();
	void addToMesh(const trio_i& position, const std::array<ofVec3f, 6>& shift);

	BlockModel& getBlock(const trio_i& position);
	ofMesh& getBuffer(const trio_i& position, BlockType type);

	map_t map_;
	std::array<BlockModel, size_t(BlockType::COUNT)> models_;
	buffer_t buffer_;
};



#endif /* SRC_GAME_WORLD_H_ */
