/*
 * Play.h
 *
 *  Created on: 12 mar 2016
 *      Author: konrad
 */

#ifndef SRC_PLAY_H_
#define SRC_PLAY_H_

#include "ofEasyCam.h"

#include "Game/GameState.h"
#include "Game/World/World.h"

//TODO: This
class Play : public GameState
{
public:
	Play();
	Play(const Play& p);
	virtual ~Play();

	virtual GameState* update(float elapsed_time);
	virtual void draw() const;
private:
	World w_;
	mutable ofEasyCam cam;
};



#endif /* SRC_PLAY_H_ */
