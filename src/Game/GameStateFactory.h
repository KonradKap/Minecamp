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
#include "Game/GameState.h"
#include "Play/PlayModel.h"
#include "Play/PlayController.h"
#include "Play/PlayView.h"
#include "Menu/MenuModel.h"
#include "Menu/MenuController.h"
#include "Menu/MenuView.h"


//TODO: Consider this not being a singleton, but a Game member
class GameStateFactory
{
public:
	static GameStateFactory& getInstance();

	GameState getState(GameStateEventType type) const;

	~GameStateFactory();
private:
	GameState getMenu() const;
	GameState getPlay(int save) const;

	GameStateFactory();
	GameStateFactory(const GameStateFactory& factory) = delete;
	GameStateFactory& operator=(const GameStateFactory&) = delete;
};



#endif /* SRC_GAME_GAMESTATEFACTORY_H_ */
