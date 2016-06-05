/*
 * Game.h
 *
 *  Created on: 10 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

#include "Utill/Registrable.h"
#include "Game/GameState.h"
#include "Play/PlayModel.h"
#include "Play/PlayController.h"
#include "Play/PlayView.h"
#include "Menu/MenuModel.h"
#include "Menu/MenuController.h"
#include "Menu/MenuView.h"
#include "Pause/PauseModel.h"
#include "Pause/PauseController.h"
#include "Pause/PauseView.h"
#include "GameStateEventType.h"

class Game : public Registrable
{
public:
	Game();

	~Game();
private:

	void registerMe(const do_register_trait&);
	void unregisterMe(const do_register_trait&);

	void onGameStateEvent(const GameStateEventType& type);
	void onPauseBreakEvent(GameState previous);
	void onQuit() const;

	GameState getMenu() const;
	GameState getPlay(int save) const;
	GameState getPause();

	std::stack<GameState> stateStack_;
	//GameStateFactory factory_;
};



#endif /* SRC_GAME_GAME_H_ */
