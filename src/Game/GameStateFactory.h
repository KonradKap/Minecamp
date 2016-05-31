/*
 * GameStateFactory.h
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_GAMESTATEFACTORY_H_
#define SRC_GAME_GAMESTATEFACTORY_H_

#include <memory>

#include "GameStateEventType.h"
#include "Menu/Menu.h"
#include "Play/Play.h"


//TODO: Consider this not being a singleton, but a Game member
class GameStateFactory
{
public:
	static GameStateFactory& getInstance();

	std::unique_ptr<GameState> getState(GameStateEventType type) const;

	~GameStateFactory();
private:
	GameStateFactory();
	GameStateFactory(const GameStateFactory& factory) = delete;
	GameStateFactory& operator=(const GameStateFactory&) = delete;
};



#endif /* SRC_GAME_GAMESTATEFACTORY_H_ */
