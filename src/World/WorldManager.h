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

#include "Utill/Registrable.h"
#include "Utill/vec3D.h"
#include "World/BlockPrototype.h"
#include "World/BufferManager.h"
#include "World/BlockType.h"
#include "World/BlockPathManager.h"

class Player;

class WorldManager : public Registrable
{
public:
	static const int X_SIZE = BufferManager::CHUNK_SIZE*BufferManager::X_CHUNK_COUNT;
	static const int Y_SIZE = BufferManager::CHUNK_SIZE*BufferManager::Y_CHUNK_COUNT;
	static const int Z_SIZE = BufferManager::CHUNK_SIZE*BufferManager::Z_CHUNK_COUNT;

	typedef std::array< std::array < std::array < BlockPrototype*, Z_SIZE >, Y_SIZE >, X_SIZE > map_t;

	typedef std::pair< vec3Di, BlockType > blockEventArgs;

	WorldManager();
	~WorldManager();

	void loadFromFile(std::istream& file);
	void saveToFile(std::ostream& file);

	void loadDefaultWorld();

	const BlockPrototype& getBlock(const vec3Di& position) const;
	const BlockPrototype& getBlock(const BlockType type) const;

	//temporary
	BlockPrototype& getBlock(const vec3Di& position);

	bool isVisible(const vec3Di& position, Side side) const;
	bool isWithin(const vec3Di& position) const;
	std::vector<Side> isOnChunkEdge(const vec3Di& position) const;
	bool areInTheSameChunk(const vec3Di& first, const vec3Di& second) const;

	ofEvent<const vec3Di&>& getChunkReloadEvent();
	ofEvent<const WorldManager::blockEventArgs&>& getBlockEvent();
private:
	void registerMe(const do_register_trait&);
	void unregisterMe(const do_register_trait&);
	void onBlockEvent(const blockEventArgs& args);

	void setupPrototypes();

	map_t map_;
	std::array<BlockPrototype, size_t(BlockType::COUNT)> models_;

	ofEvent<const vec3Di&> chunkReloadRequest_;

	ofEvent<const WorldManager::blockEventArgs&> blockEvent_;
	//ofEvent<const vec3Di&> destroyedBlockEvent_;

};

#include "Play/Player.h"


#endif /* SRC_GAME_WORLD_H_ */
