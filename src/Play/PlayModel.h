/*
 * Play.h
 *
 *  Created on: 12 mar 2016
 *      Author: konrad
 */

#ifndef SRC_PLAY_H_
#define SRC_PLAY_H_


#include "Game/GameState.h"
#include "Play/PlayView.h"
#include "Play/Player.h"
#include "World/BufferManager.h"
#include "Play/SaveFileManager.h"
#include "Play/EquipmentManager.h"

#include "Utill/vec3D.h"


//TODO: This
class PlayModel : public Model
{
public:
	PlayModel(int save_state);
	PlayModel(const PlayModel& p) = delete;
	virtual ~PlayModel();

	std::pair<vec3Di, vec3Di> findTargetedBlock() const;

	Player& getPlayer();
	const Player& getPlayer() const;

	WorldManager& getWorldManager();
	const WorldManager& getWorldManager() const;

	EquipmentManager& getEquipmentManager();
	const EquipmentManager& getEquipmentManager() const;

	const BufferManager& getBufferManager() const;

private:
	void registerMe(const do_register_trait&);
	void unregisterMe(const do_register_trait&);

	WorldManager world_manager_;
	BufferManager buffer_manager_;
	SaveFileManager save_file_manager_;
	EquipmentManager equipment_manager_;
	Player player_;


	//mutable ofEasyCam cam;
};



#endif /* SRC_PLAY_H_ */
