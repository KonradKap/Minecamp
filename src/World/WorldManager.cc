/*
 * World.cc
 *
 *  Created on: 17 mar 2016
 *      Author: konrad
 */

#include "World/WorldManager.h"

WorldManager::WorldManager() :
	Registrable(),
	map_(),
	models_()
	//buffer_()

{
	setupPrototypes();
}

WorldManager::~WorldManager()
{
}

void WorldManager::registerMe(const do_register_trait&)
{
	ofAddListener(getBlockEvent(), this, &WorldManager::onBlockEvent);
}

void WorldManager::unregisterMe(const do_register_trait&)
{
	ofRemoveListener(getBlockEvent(), this, &WorldManager::onBlockEvent);
}

void WorldManager::setupPrototypes()
{
	const BlockPathManager MANAGER;
	for(unsigned i = 0; i < unsigned(BlockType::COUNT); ++i)
			models_[i] = BlockPrototype(BlockType(i), MANAGER.get(BlockType(i)));
}

void WorldManager::loadFromFile(std::istream& file)
{
	for(auto& itX : map_)
	for(auto& itY : itX)
	for(auto& itZ : itY)
	{
		int type;
		file >> type;
		itZ = &models_[type];
	}
}
	//TODO:
void WorldManager::saveToFile(std::ostream& file)
{
	for(auto& itX : map_)
	for(auto& itY : itX)
	for(auto& itZ : itY)
	{
		file << int(itZ->getType()) << " ";
	}

}

void WorldManager::onBlockEvent(const blockEventArgs& args)
{
	map_[args.first.x][args.first.y][args.first.z] = &models_[unsigned(args.second)];
	const vec3Di BUFFER_INDEX = args.first/BufferManager::CHUNK_SIZE;
	Registrable::notify(chunkReloadRequest_, BUFFER_INDEX);

	std::vector<Side> neighbour_chunks = isOnChunkEdge(args.first);
	for(auto side : neighbour_chunks)
		Registrable::notify(chunkReloadRequest_, BUFFER_INDEX + vec3Di::make_unit_vector(side));

}

void WorldManager::loadDefaultWorld()
{
	BlockPrototype* const DIRT_PTR = &models_[1];
	BlockPrototype* const AIR_PTR = &models_[0];

	for(unsigned x = 0; x < map_.size(); ++x)
	for(unsigned y = 0; y < map_[x].size(); ++y)
	for(unsigned z = 0; z < map_[x][y].size(); ++z)
	{
		if(y < Y_SIZE/2)
			map_[x][y][z] = DIRT_PTR;
		else
			map_[x][y][z] = AIR_PTR;
	}
}

bool WorldManager::isVisible(const vec3Di& position, Side side) const
{
	if(getBlock(position).isGas())
		return false;

	const vec3Di NEXT = position + vec3Di::make_unit_vector(side);

	if(NEXT.x >= X_SIZE or NEXT.x < 0 or
	   NEXT.y >= Y_SIZE or NEXT.y < 0 or
	   NEXT.z >= Z_SIZE or NEXT.z < 0)
		return true;

	if(getBlock(position).isSolid())
		return getBlock(NEXT).isTransparent();
	if(getBlock(position).isLiquid())
		return getBlock(NEXT).isGas();
	return false;
}

bool WorldManager::isWithin(const vec3Di& position) const
{
	if(position.x < 0 or position.x >= X_SIZE)
		return false;
	if(position.y < 0 or position.y >= Y_SIZE)
		return false;
	if(position.z < 0 or position.z >= Z_SIZE)
		return false;
	return true;
}

std::vector<Side> WorldManager::isOnChunkEdge(const vec3Di& position) const
{
	std::vector<Side> sides;
	for(unsigned i = 0; i < unsigned(Side::COUNT); ++i)
		if(!areInTheSameChunk(position, position+vec3Di::make_unit_vector(Side(i))))
			sides.push_back(Side(i));

	return sides;

}

bool WorldManager::areInTheSameChunk(const vec3Di& first, const vec3Di& second) const
{
	return first/BufferManager::CHUNK_SIZE == second/BufferManager::CHUNK_SIZE;
}

const BlockPrototype& WorldManager::getBlock(const vec3Di& position) const
{
	return const_cast<WorldManager*>(this)->getBlock(position);
}

BlockPrototype& WorldManager::getBlock(const vec3Di& position)
{
	return *map_[position.x][position.y][position.z];
}

const BlockPrototype& WorldManager::getBlock(const BlockType type) const
{
	return models_[unsigned(type)];
}

ofEvent<const vec3Di&>& WorldManager::getChunkReloadEvent()
{
	return chunkReloadRequest_;
}

ofEvent<const WorldManager::blockEventArgs&>& WorldManager::getBlockEvent()
{
	return blockEvent_;
}

