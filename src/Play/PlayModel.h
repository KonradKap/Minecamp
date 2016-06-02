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


//TODO: This
class PlayModel : public Model
{
public:
	PlayModel(int save_state);
	PlayModel(const PlayModel& p) = delete;
	virtual ~PlayModel();

	Player& getPlayer() {return player_; }
	const Player& getPlayer() const {return player_; }
	const WorldManager& getWorldManager() const {return world_manager_;}

	const BufferManager& getBufferManager() const {return buffer_manager_;}
private:
	WorldManager world_manager_;
	BufferManager buffer_manager_;
	SaveFileManager save_file_manager_;
	Player player_;
	//mutable ofEasyCam cam;
};



#endif /* SRC_PLAY_H_ */
