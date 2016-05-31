/*
 * Game.h
 *
 *  Created on: 10 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

#include <cassert>
#include <memory>

enum class GameStateEventType;

class GameState;
class View;

class Game
{
public:
	Game();

	~Game();

	void update(float elapsed_time);
	void draw() const;

private:
	void onStateSwitch(const GameStateEventType& type);
	std::unique_ptr<GameState> state_;
	std::unique_ptr<View> view_;
};

#include "Game/GameStateFactory.h"
#include "GameStateEventType.h"
#include "Utill/View.h"

#endif /* SRC_GAME_GAME_H_ */
