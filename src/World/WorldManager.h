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

	//void registerListeners();

	void loadFromFile(std::istream& file);
	void saveToFile(std::ostream& file);

	void loadDefaultWorld();

	const BlockPrototype& getBlock(const vec3Di& position) const;
	const BlockPrototype& getBlock(const BlockType type) const;

	//temporary
	BlockPrototype& getBlock(const vec3Di& position);

	bool isVisible(const vec3Di& position, Side side) const;
	bool isWithin(const vec3Di& position) const;

	ofEvent<const vec3Di&>& getChunkReloadEvent();
	ofEvent<const WorldManager::blockEventArgs&>& getPlacedBlockEvent();
	ofEvent<const vec3Di&>& getDestroyedBlockEvent();
private:
	void onBlockDestruction(const vec3Di& args);
	void onBlockPlacement(const blockEventArgs& args);

	//void setupBuffer();
	void setupPrototypes();



	map_t map_;
	std::array<BlockPrototype, size_t(BlockType::COUNT)> models_;

	ofEvent<const vec3Di&> chunkReloadRequest_;

	ofEvent<const WorldManager::blockEventArgs&> placedBlockEvent_;
	ofEvent<const vec3Di&> destroyedBlockEvent_;

};

#include "Play/Player.h"


#endif /* SRC_GAME_WORLD_H_ */
