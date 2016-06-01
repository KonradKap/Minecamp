/*
 * Game.h
 *
 *  Created on: 10 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

#include "Game/GameState.h"
#include "Game/GameStateFactory.h"
#include "GameStateEventType.h"

class Game
{
public:
	Game();

	~Game();
private:
	void onStateSwitch(const GameStateEventType& type);
	GameState state_;
};



#endif /* SRC_GAME_GAME_H_ */
