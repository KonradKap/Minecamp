/*
 * World.cc
 *
 *  Created on: 17 mar 2016
 *      Author: konrad
 */

#include "Game/World/World.h"

World::World() :
	map_(),
	models_(),
	buffer_()

{
	setup();
}

World::~World()
{
}

void World::setup()
{
	ofDisableArbTex();
	ofEnableDepthTest();
	BlockPathManager manager;
	models_ = {
				BlockModel(BlockType::AIR, manager.get(BlockType::AIR)),
				BlockModel(BlockType::DIRT, manager.get(BlockType::DIRT)),
				BlockModel(BlockType::STONE, manager.get(BlockType::STONE)),
				BlockModel(BlockType::WATER, manager.get(BlockType::WATER)),
				BlockModel(BlockType::FIRE, manager.get(BlockType::FIRE)),
			 };

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

void World::setupBuffer()
{
	ofSetColor( 255, 255, 255 );

	const std::array<ofVec3f, 8> VERTICES =
	{
		ofVec3f(0, 			   	  0, 				0				),
		ofVec3f(BlockModel::SIZE, 0, 				0				),
		ofVec3f(0, 			      BlockModel::SIZE, 0			 	),
		ofVec3f(0, 			      0, 				BlockModel::SIZE),
		ofVec3f(BlockModel::SIZE, BlockModel::SIZE, 0				),
		ofVec3f(BlockModel::SIZE, 0, 				BlockModel::SIZE),
		ofVec3f(0, 			      BlockModel::SIZE, BlockModel::SIZE),
		ofVec3f(BlockModel::SIZE, BlockModel::SIZE, BlockModel::SIZE)
	};

	const std::array<std::array<ofVec3f, 6>, unsigned(Side::COUNT)> SIDE_VERTICES =
	{
		std::array<ofVec3f, 6>({VERTICES[3], VERTICES[5], VERTICES[7], VERTICES[3], VERTICES[6], VERTICES[7]}),
		std::array<ofVec3f, 6>({VERTICES[0], VERTICES[1], VERTICES[4], VERTICES[0], VERTICES[2], VERTICES[4]}),
		std::array<ofVec3f, 6>({VERTICES[0], VERTICES[1], VERTICES[5], VERTICES[0], VERTICES[3], VERTICES[5]}),
		std::array<ofVec3f, 6>({VERTICES[2], VERTICES[4], VERTICES[7], VERTICES[2], VERTICES[6], VERTICES[7]}),
		std::array<ofVec3f, 6>({VERTICES[0], VERTICES[3], VERTICES[6], VERTICES[0], VERTICES[2], VERTICES[6]}),
		std::array<ofVec3f, 6>({VERTICES[1], VERTICES[4], VERTICES[7], VERTICES[1], VERTICES[5], VERTICES[7]})
	};

/*
	for(unsigned x = 0; x < buffer_.size(); ++x)
		for(unsigned y = 0; y < buffer_[x].size(); ++y)
			for(unsigned z = 0; z < buffer_[x][y].size(); ++z)
				for(size_t i = 0; i < size_t(BlockType::COUNT); ++i)
				{
					//buffer_[x][y][z][i].
					//buffer_[x][y][z][i].setMode(OF_PRIMITIVE_TRIANGLES);
					//buffer_[x][y][z][i].addTexCoords({ofVec2f(0, 0), ofVec2f(16, 0), ofVec2f(0, 16), ofVec2f(16, 16)});
				}
*/

	for(unsigned x = 0; x < map_.size(); ++x)
		for(unsigned y = 0; y < map_[x].size(); ++y)
			for(unsigned z = 0; z < map_[x][y].size(); ++z)
			{
				for(unsigned i = 0; i < unsigned(Side::COUNT); ++i)
					if(isVisible(trio_i(x, y, z), Side(i)))
						addToMesh(trio_i(x, y, z), SIDE_VERTICES[i]);
			}
}

	//TODO:
void World::loadFromFile(std::ifstream& file)
{
	assert(false);
}
	//TODO:
void World::saveToFile(std::ofstream& file)
{
	assert(false);
}
	//TODO:
void World::draw() const
{
	for(const auto& itX : buffer_)
		for(const auto& itY : itX)
			for(const auto& itZ : itY)
				for(unsigned i = 0; i < unsigned(BlockType::COUNT); ++i)
				{
					models_[i].getTexture().getTexture().bind();
					itZ[i].draw();
					models_[i].getTexture().getTexture().unbind();
				}
}

//TODO: Update buffer on these
void World::onBlockDestruction(const trio_i& position)
{
	getBlock(position) = models_[unsigned(BlockType::AIR)];
}

void World::onBlockPlacement(const trio_i& position, BlockType type)
{
	getBlock(position) = models_[unsigned(type)];
}

bool World::isVisible(const trio_i& position, Side side) const
{
	if(getBlock(position).isGas())
		return false;

	const trio_i NEXT = position + trio_i::make_unit_vector(side);

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
//TODO: Make it use VBO for more FPS-es
void World::addToMesh(const trio_i& position, const std::array<ofVec3f, 6>& shift)
{
	const trio_i BUFFER = trio_i(position.x/CHUNK_SIZE, position.y/CHUNK_SIZE, position.z/CHUNK_SIZE);
	const ofVec3f MESH_POSITION = ofVec3f(position.x*BlockModel::SIZE, position.y*BlockModel::SIZE, position.z*BlockModel::SIZE);
	const BlockType TYPE = getBlock(position).getType();

	ofMesh& mesh = getBuffer(BUFFER, TYPE);
	for(const auto& it : shift)
		mesh.addVertex(MESH_POSITION + it);

	mesh.addTexCoords({ofVec2f(0, 0), ofVec2f(1, 0), ofVec2f(1, 1), ofVec2f(0, 0), ofVec2f(0, 1), ofVec2f(1, 1)});
}

const BlockModel& World::getBlock(const trio_i& position) const
{
	return const_cast<World*>(this)->getBlock(position);
}

BlockModel& World::getBlock(const trio_i& position)
{
	return *map_[position.x][position.y][position.z];
}

const ofMesh& World::getBuffer(const trio_i& position, BlockType type) const
{
	return const_cast<World*>(this)->getBuffer(position, type);
}

ofMesh& World::getBuffer(const trio_i& position, BlockType type)
{
	return buffer_[position.x][position.y][position.z][unsigned(type)];
}
