/*
 * World.cc
 *
 *  Created on: 17 mar 2016
 *      Author: konrad
 */

#include "World/WorldManager.h"

WorldManager::WorldManager() :
	map_(),
	models_()
	//buffer_()

{
	ofDisableArbTex();
	setupPrototypes();
	ofAddListener(getDestroyedBlockEvent(), this, &WorldManager::onBlockDestruction);
	ofAddListener(getPlacedBlockEvent(), this, &WorldManager::onBlockPlacement);
	/** TEMPORARY */ //loadDefaultWorld();
}

WorldManager::~WorldManager()
{
	ofEnableArbTex();
	ofRemoveListener(getDestroyedBlockEvent(), this, &WorldManager::onBlockDestruction);
	ofRemoveListener(getPlacedBlockEvent(), this, &WorldManager::onBlockPlacement);
}
/*
void WorldManager::registerListeners(PlayerController& p)
{

}
*/
void WorldManager::setupPrototypes()
{
	const BlockPathManager MANAGER;
	for(unsigned i = 0; i < unsigned(BlockType::COUNT); ++i)
			models_[i] = BlockPrototype(BlockType(i), MANAGER.get(BlockType(i)));
}
/*
void WorldManager::setupBuffer()
{
	for(unsigned x = 0; x < buffer_.size(); ++x)
	for(unsigned y = 0; y < buffer_[x].size(); ++y)
	for(unsigned z = 0; z < buffer_[x][y].size(); ++z)
		reloadChunk(vec3Di(x, y, z));
}
*/
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

void WorldManager::onBlockDestruction(const vec3Di& args)
{
	map_[args.x][args.y][args.z] = &models_[unsigned(BlockType::AIR)];
	const vec3Di BUFFER_INDEX = args/BufferManager::CHUNK_SIZE;
	ofNotifyEvent(chunkReloadRequest_, BUFFER_INDEX, this);

	std::vector<Side> neighbour_chunks = isOnChunkEdge(args);
	for(auto side : neighbour_chunks)
		ofNotifyEvent(chunkReloadRequest_, BUFFER_INDEX + vec3Di::make_unit_vector(side), this);

}

void WorldManager::onBlockPlacement(const blockEventArgs& args)
{
	map_[args.first.x][args.first.y][args.first.z] = &models_[unsigned(args.second)];
	ofNotifyEvent(chunkReloadRequest_, args.first/BufferManager::CHUNK_SIZE, this);
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
	//if(position.x%BufferManager::CHUNK_SIZE == 0)
	//	return false;
	return sides;

}

bool WorldManager::areInTheSameChunk(const vec3Di& first, const vec3Di& second) const
{
	return first/BufferManager::CHUNK_SIZE == second/BufferManager::CHUNK_SIZE;
}
/*
void WorldManager::addToMesh(const vec3Di& position, const std::array<ofVec3f, 6>& shift)
{
	const vec3Di BUFFER = vec3Di(position.x/CHUNK_SIZE, position.y/CHUNK_SIZE, position.z/CHUNK_SIZE);
	const ofVec3f MESH_POSITION = ofVec3f(position.x*BlockPrototype::SIZE, position.y*BlockPrototype::SIZE, position.z*BlockPrototype::SIZE);
	const BlockType TYPE = getBlock(position).getType();

	ofMesh& mesh = getBuffer(BUFFER, TYPE);
	for(const auto& it : shift)
		mesh.addVertex(MESH_POSITION + it);

	mesh.addTexCoords({ofVec2f(0, 0), ofVec2f(1, 0), ofVec2f(1, 1), ofVec2f(0, 0), ofVec2f(0, 1), ofVec2f(1, 1)});
}
*/
const BlockPrototype& WorldManager::getBlock(const vec3Di& position) const
{
	return const_cast<WorldManager*>(this)->getBlock(position);
}

BlockPrototype& WorldManager::getBlock(const vec3Di& position)
{
	return *map_[position.x][position.y][position.z];
}
/*
const WorldManager::buffer_t& WorldManager::getBuffer() const
{
	return buffer_;
}

const ofMesh& WorldManager::getBuffer(const vec3Di& position, BlockType type) const
{
	return const_cast<WorldManager*>(this)->getBuffer(position, type);
}

ofMesh& WorldManager::getBuffer(const vec3Di& position, BlockType type)
{
	return buffer_[position.x][position.y][position.z][unsigned(type)];
}
*/
const BlockPrototype& WorldManager::getBlock(const BlockType type) const
{
	return models_[unsigned(type)];
}

ofEvent<const vec3Di&>& WorldManager::getChunkReloadEvent()
{
	return chunkReloadRequest_;
}

ofEvent<const WorldManager::blockEventArgs&>& WorldManager::getPlacedBlockEvent()
{
	return placedBlockEvent_;
}

ofEvent<const vec3Di&>& WorldManager::getDestroyedBlockEvent()
{
	return destroyedBlockEvent_;
}

