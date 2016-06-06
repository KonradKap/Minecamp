/*
 * BufferManager.h
 *
 *  Created on: 2 cze 2016
 *      Author: konrad
 */

#ifndef SRC_WORLD_BUFFERMANAGER_H_
#define SRC_WORLD_BUFFERMANAGER_H_

#include "ofVbo.h"
#include "ofVboMesh.h"
#include "of3dPrimitives.h"
#include "ofGraphics.h"

#include "Utill/Registrable.h"
#include "Utill/vec3D.h"

class WorldManager;

class BufferManager : public Registrable
{
public:
	static const int CHUNK_SIZE = 16;
	static const int X_CHUNK_COUNT = 1;
	static const int Y_CHUNK_COUNT = 1;
	static const int Z_CHUNK_COUNT = 1;


	typedef std::array< ofVboMesh, size_t(BlockType::COUNT) > chunk_t;
	typedef std::array< std::array< std::array < chunk_t, Z_CHUNK_COUNT >, Y_CHUNK_COUNT >, X_CHUNK_COUNT > buffer_t;

	BufferManager(WorldManager& source);
	~BufferManager();

	void setup();

	const buffer_t& getBuffer() const;
	const ofVboMesh& getBuffer(const vec3Di& position, BlockType type) const;

	bool isValid(const vec3Di& position) const;
private:
	void registerMe(const do_register_trait&);
	void unregisterMe(const do_register_trait&);

	void onReloadChunkRequest(const vec3Di& position);
	void clearChunk(const vec3Di& position);
	void addToMesh(const vec3Di& position, const std::array<ofVec3f, 6>& shift);

	ofVboMesh& getBuffer(const vec3Di& position, BlockType type);

	buffer_t buffer_;
	WorldManager& source_;

	static const std::array<ofVec3f, 8> VERTICES;
	static const std::array<std::array<ofVec3f, 6>, unsigned(Side::COUNT)> SIDE_VERTICES;
};



#endif /* SRC_WORLD_BUFFERMANAGER_H_ */
