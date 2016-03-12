/*
 * Game.h
 *
 *  Created on: 10 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

#include <cassert>

class GameState;

class Game
{
	public:
		Game();

		~Game();

		//void handleInput();
		bool update(float elapsed_time);
		void draw() const;

	private:
//TODO: Make this a unique_ptr?
		GameState* state_;

};

#include "Game/GameState.h"
#include "Game/Menu/Menu.h"

#endif /* SRC_GAME_GAME_H_ */
