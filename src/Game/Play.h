/*
 * Play.h
 *
 *  Created on: 12 mar 2016
 *      Author: konrad
 */

#ifndef SRC_PLAY_H_
#define SRC_PLAY_H_

#include "Game/GameState.h"

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

};



#endif /* SRC_PLAY_H_ */
