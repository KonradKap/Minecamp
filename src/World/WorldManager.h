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

#include "../Utill/vec3D.h"
#include "ofVbo.h"
#include "ofVboMesh.h"
#include "of3dPrimitives.h"
#include "ofGraphics.h"

#include "World/BlockModel.h"

class Player;

class WorldManager
{
public:
	static const int X_SIZE = 16;
	static const int Y_SIZE = 16;
	static const int Z_SIZE = 16;
	static const int CHUNK_SIZE = 16;

	typedef std::array< std::array < std::array < BlockModel*, Z_SIZE >, Y_SIZE >, X_SIZE > map_t;
	typedef std::array< ofMesh, size_t(BlockType::COUNT) > chunk_t;
	typedef std::array< std::array< std::array < chunk_t, Z_SIZE/CHUNK_SIZE >, Y_SIZE/CHUNK_SIZE >, X_SIZE/CHUNK_SIZE > buffer_t;
	typedef std::pair< vec3Di, BlockType > blockEventArgs;

	WorldManager();
	WorldManager(const WorldManager& w) = delete;
	~WorldManager();

	void registerListeners(Player& p);

	void loadFromFile(std::ifstream& file);
	void saveToFile(std::ofstream& file);

	void loadDefaultWorld();

	const BlockModel& getBlock(const vec3Di& position) const;

	const buffer_t& getBuffer() const;
	const ofMesh& getBuffer(const vec3Di& position, BlockType type) const;

	const BlockModel& getModel(const BlockType type) const;
private:
	void onBlockDestruction(blockEventArgs& args);
	void onBlockPlacement(blockEventArgs& args);

	bool isVisible(const vec3Di& position, Side side) const;

	void setupBuffer();
	void setupModels();

	void reloadChunk(const vec3Di& position);
	void addToMesh(const vec3Di& position, const std::array<ofVec3f, 6>& shift);

	BlockModel& getBlock(const vec3Di& position);
	ofMesh& getBuffer(const vec3Di& position, BlockType type);

	map_t map_;
	std::array<BlockModel, size_t(BlockType::COUNT)> models_;
	buffer_t buffer_;
};

#include "Play/Player.h"


#endif /* SRC_GAME_WORLD_H_ */
