/*
 * Play.h
 *
 *  Created on: 12 mar 2016
 *      Author: konrad
 */

#ifndef SRC_PLAY_H_
#define SRC_PLAY_H_

#include "../World/WorldManager.h"
#include "Game/GameState.h"
#include "Play/PlayView.h"

//TODO: This
class Play : public GameState
{
public:
	Play();
	Play(const Play& p);
	virtual ~Play();

	void update(float elapsed_time);
	std::unique_ptr<View> getDefaultView() const;
private:
	WorldManager w_;
	//mutable ofEasyCam cam;
};



#endif /* SRC_PLAY_H_ */
