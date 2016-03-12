/*
 * GameState.h
 *
 *  Created on: 10 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_GAMESTATE_H_
#define SRC_GAME_GAMESTATE_H_

class GameState
{
public:
	GameState() {}
	//GameState(const GameState& gs);
	virtual ~GameState() {}

	virtual void handleInput() = 0;
	virtual GameState* update(float elapsed_time) = 0;
	virtual void draw() const = 0;
private:
};



#endif /* SRC_GAME_GAMESTATE_H_ */
