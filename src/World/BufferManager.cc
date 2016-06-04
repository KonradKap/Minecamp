/*
 * BufferManager.cc
 *
 *  Created on: 2 cze 2016
 *      Author: konrad
 */

#include "World/BufferManager.h"
#include "World/WorldManager.h"

	/** UGLY WARNING */
const std::array<ofVec3f, 8> BufferManager::VERTICES
	{
		ofVec3f(0, 			   	  		0, 						0					),
		ofVec3f(BlockPrototype::SIZE, 	0, 						0					),
		ofVec3f(0, 			      		BlockPrototype::SIZE, 	0			 		),
		ofVec3f(0, 			     		0, 						BlockPrototype::SIZE),
		ofVec3f(BlockPrototype::SIZE, 	BlockPrototype::SIZE, 	0					),
		ofVec3f(BlockPrototype::SIZE, 	0, 						BlockPrototype::SIZE),
		ofVec3f(0, 			      		BlockPrototype::SIZE, 	BlockPrototype::SIZE),
		ofVec3f(BlockPrototype::SIZE, 	BlockPrototype::SIZE, 	BlockPrototype::SIZE)
	};

const std::array<std::array<ofVec3f, 6>, unsigned(Side::COUNT)> BufferManager::SIDE_VERTICES
	{
		std::array<ofVec3f, 6>({VERTICES[3], VERTICES[5], VERTICES[7], VERTICES[3], VERTICES[6], VERTICES[7]}),
		std::array<ofVec3f, 6>({VERTICES[0], VERTICES[1], VERTICES[4], VERTICES[0], VERTICES[2], VERTICES[4]}),
		std::array<ofVec3f, 6>({VERTICES[1], VERTICES[4], VERTICES[7], VERTICES[1], VERTICES[5], VERTICES[7]}),
		std::array<ofVec3f, 6>({VERTICES[0], VERTICES[3], VERTICES[6], VERTICES[0], VERTICES[2], VERTICES[6]}),
		std::array<ofVec3f, 6>({VERTICES[0], VERTICES[1], VERTICES[5], VERTICES[0], VERTICES[3], VERTICES[5]}),
		std::array<ofVec3f, 6>({VERTICES[2], VERTICES[4], VERTICES[7], VERTICES[2], VERTICES[6], VERTICES[7]}),
	};

BufferManager::BufferManager(WorldManager& source) :
	Registrable(),
	buffer_(),
	source_(source)
{
}

BufferManager::~BufferManager()
{
}

void BufferManager::registerMe(const do_register_trait&)
{
	ofAddListener(source_.getChunkReloadEvent(), this, &BufferManager::onReloadChunkRequest);
}

void BufferManager::unregisterMe(const do_register_trait&)
{
	ofRemoveListener(source_.getChunkReloadEvent(), this, &BufferManager::onReloadChunkRequest);
}

ofVboMesh& BufferManager::getBuffer(const vec3Di& position, BlockType type)
{
	return buffer_[position.x][position.y][position.z][unsigned(type)];
}

const BufferManager::buffer_t& BufferManager::getBuffer() const
{
	return buffer_;
}

const ofVboMesh& BufferManager::getBuffer(const vec3Di& position, BlockType type) const
{
	return const_cast<BufferManager*>(this)->getBuffer(position, type);
}

void BufferManager::onReloadChunkRequest(const vec3Di& position)
{
	if(!isValid(position))
		return;
	clearChunk(position);
	for(int x = position.x*CHUNK_SIZE; x < (position.x+1)*CHUNK_SIZE; ++x)
	for(int y = position.y*CHUNK_SIZE; y < (position.y+1)*CHUNK_SIZE; ++y)
	for(int z = position.z*CHUNK_SIZE; z < (position.z+1)*CHUNK_SIZE; ++z)
	{
		for(unsigned i = 0; i < unsigned(Side::COUNT); ++i)
			if(source_.isVisible(vec3Di(x, y, z), Side(i)))
				addToMesh(vec3Di(x, y, z), SIDE_VERTICES[i]);
	}
}

bool BufferManager::isValid(const vec3Di& position) const
{
	if(position.x < 0 or position.x >= X_CHUNK_COUNT)
		return false;
	if(position.y < 0 or position.y >= Y_CHUNK_COUNT)
		return false;
	if(position.z < 0 or position.z >= Z_CHUNK_COUNT)
		return false;

	return true;
}

void BufferManager::setup()
{
	for(unsigned x = 0; x < buffer_.size(); ++x)
	for(unsigned y = 0; y < buffer_[x].size(); ++y)
	for(unsigned z = 0; z < buffer_[x][y].size(); ++z)
		onReloadChunkRequest(vec3Di(x, y, z));
}

void BufferManager::clearChunk(const vec3Di& position)
{
	for(auto& it : buffer_[position.x][position.y][position.z])
		it.clear();
}

void BufferManager::addToMesh(const vec3Di& position, const std::array<ofVec3f, 6>& shift)
{
	const vec3Di BUFFER = vec3Di(position.x/CHUNK_SIZE, position.y/CHUNK_SIZE, position.z/CHUNK_SIZE);
	const ofVec3f MESH_POSITION = ofVec3f(position.x*BlockPrototype::SIZE, position.y*BlockPrototype::SIZE, position.z*BlockPrototype::SIZE);
	const BlockType TYPE = source_.getBlock(position).getType();

	ofVboMesh& mesh = getBuffer(BUFFER, TYPE);
	for(const auto& it : shift)
		mesh.addVertex(MESH_POSITION + it);

	mesh.addTexCoords({ofVec2f(0, 0), ofVec2f(1, 0), ofVec2f(1, 1), ofVec2f(0, 0), ofVec2f(0, 1), ofVec2f(1, 1)});
}


