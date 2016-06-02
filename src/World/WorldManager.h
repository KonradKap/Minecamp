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

#include "Utill/vec3D.h"
#include "World/BlockPrototype.h"

class Player;

class WorldManager
{
public:
	static const int X_SIZE = 16;
	static const int Y_SIZE = 16;
	static const int Z_SIZE = 16;

	typedef std::array< std::array < std::array < BlockPrototype*, Z_SIZE >, Y_SIZE >, X_SIZE > map_t;

	typedef std::pair< vec3Di, BlockType > blockEventArgs;

	WorldManager();
	//WorldManager(const WorldManager& w) = delete;
	~WorldManager();

	void registerListeners(Player& p);

	void loadFromFile(std::istream& file);
	void saveToFile(std::ostream& file);

	void loadDefaultWorld();

	const BlockPrototype& getBlock(const vec3Di& position) const;
	const BlockPrototype& getBlock(const BlockType type) const;

	bool isVisible(const vec3Di& position, Side side) const;

	ofEvent<const vec3Di&>& getChunkReloadEvent() const;
private:
	void onBlockDestruction(vec3Di& args);
	void onBlockPlacement(blockEventArgs& args);

	//void setupBuffer();
	void setupPrototypes();

	BlockPrototype& getBlock(const vec3Di& position);

	map_t map_;
	std::array<BlockPrototype, size_t(BlockType::COUNT)> models_;

	mutable ofEvent<const vec3Di&> chunkReloadRequest_;
};

#include "Play/Player.h"


#endif /* SRC_GAME_WORLD_H_ */
