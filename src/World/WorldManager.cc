/*
 * World.cc
 *
 *  Created on: 17 mar 2016
 *      Author: konrad
 */

#include "WorldManager.h"

WorldManager::WorldManager() :
	map_(),
	models_(),
	buffer_()

{
	ofDisableArbTex();
	setupModels();
	/** TEMPORARY */ loadDefaultWorld();
}

WorldManager::~WorldManager()
{
	ofEnableArbTex();
}

void WorldManager::registerListeners(Player& p)
{
	ofAddListener(p.getDestroyedBlockEvent(), this, &WorldManager::onBlockDestruction);
	ofAddListener(p.getPlacedBlockEvent(), this, &WorldManager::onBlockPlacement);
}

void WorldManager::setupModels()
{
	const BlockPathManager MANAGER;
	for(unsigned i = 0; i < unsigned(BlockType::COUNT); ++i)
			models_[i] = BlockModel(BlockType(i), MANAGER.get(BlockType(i)));
}

void WorldManager::setupBuffer()
{
	for(unsigned x = 0; x < buffer_.size(); ++x)
	for(unsigned y = 0; y < buffer_[x].size(); ++y)
	for(unsigned z = 0; z < buffer_[x][y].size(); ++z)
		reloadChunk(vec3Di(x, y, z));
}

	//TODO:
void WorldManager::loadFromFile(std::ifstream& file)
{
	assert(false);

	setupBuffer();
}
	//TODO:
void WorldManager::saveToFile(std::ofstream& file)
{
	assert(false);
}

void WorldManager::reloadChunk(const vec3Di& position)
{
	//throw if position out of range
	for(int x = position.x*CHUNK_SIZE; x < (position.x+1)*CHUNK_SIZE; ++x)
	for(int y = position.y*CHUNK_SIZE; y < (position.y+1)*CHUNK_SIZE; ++y)
	for(int z = position.z*CHUNK_SIZE; z < (position.z+1)*CHUNK_SIZE; ++z)
	{
		for(unsigned i = 0; i < unsigned(Side::COUNT); ++i)
			if(isVisible(vec3Di(x, y, z), Side(i)))
				addToMesh(vec3Di(x, y, z), SIDE_VERTICES[i]);
	}
}

//TODO: Update buffer on these
void WorldManager::onBlockDestruction(blockEventArgs& args)
{
	getBlock(args.first) = models_[unsigned(BlockType::AIR)];
	reloadChunk(args.first/CHUNK_SIZE);
}

void WorldManager::onBlockPlacement(blockEventArgs& args)
{
	getBlock(args.first) = models_[unsigned(args.second)];
	reloadChunk(args.first/CHUNK_SIZE);
}

void WorldManager::loadDefaultWorld()
{
	BlockModel* const DIRT_PTR = &models_[1];
	BlockModel* const AIR_PTR = &models_[0];

	for(unsigned x = 0; x < map_.size(); ++x)
	for(unsigned y = 0; y < map_[x].size(); ++y)
	for(unsigned z = 0; z < map_[x][y].size(); ++z)
	{
		if(y < Y_SIZE/2)
			map_[x][y][z] = DIRT_PTR;
		else
			map_[x][y][z] = AIR_PTR;
	}

	setupBuffer();
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

void WorldManager::addToMesh(const vec3Di& position, const std::array<ofVec3f, 6>& shift)
{
	const vec3Di BUFFER = vec3Di(position.x/CHUNK_SIZE, position.y/CHUNK_SIZE, position.z/CHUNK_SIZE);
	const ofVec3f MESH_POSITION = ofVec3f(position.x*BlockModel::SIZE, position.y*BlockModel::SIZE, position.z*BlockModel::SIZE);
	const BlockType TYPE = getBlock(position).getType();

	ofMesh& mesh = getBuffer(BUFFER, TYPE);
	for(const auto& it : shift)
		mesh.addVertex(MESH_POSITION + it);

	mesh.addTexCoords({ofVec2f(0, 0), ofVec2f(1, 0), ofVec2f(1, 1), ofVec2f(0, 0), ofVec2f(0, 1), ofVec2f(1, 1)});
}

const BlockModel& WorldManager::getBlock(const vec3Di& position) const
{
	return const_cast<WorldManager*>(this)->getBlock(position);
}

BlockModel& WorldManager::getBlock(const vec3Di& position)
{
	return *map_[position.x][position.y][position.z];
}

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

const BlockModel& WorldManager::getModel(const BlockType type) const
{
	return models_[unsigned(type)];
}
