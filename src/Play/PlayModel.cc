/*
 * Play.cc
 *
 *  Created on: 12 mar 2016
 *      Author: konrad
 */

#include "PlayModel.h"

PlayModel::PlayModel(int save_state) :
	Model(),
	world_manager_(),
	save_file_manager_(save_state, world_manager_),
	player_()
{
	world_manager_.registerListeners(player_);
	save_file_manager_.load();
}
/*
Play::Play(const Play& p)
{
}
*/
PlayModel::~PlayModel()
{
	save_file_manager_.save();
}


/*
void Play::draw() const
{
	cam.begin();

		w_.draw();

	cam.end();
}
*/



