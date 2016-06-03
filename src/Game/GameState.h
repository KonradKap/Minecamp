/*
 * GameState.h
 *
 *  Created on: 10 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_GAMESTATE_H_
#define SRC_GAME_GAMESTATE_H_

#include <memory>

enum class GameStateEventType;

#include "ofEvents.h"

#include "View.h"
#include "Controller.h"
#include "Model.h"

class GameState
{
public:
	typedef std::unique_ptr<View> view_ptr;
	typedef std::unique_ptr<Model> model_ptr;
	typedef std::unique_ptr<Controller> controller_ptr;

	GameState(model_ptr model, view_ptr view, controller_ptr controller);
	GameState(GameState&& state);
	GameState& operator= (GameState&& state);
	~GameState();

private:

	std::unique_ptr<Model> model_;
	std::unique_ptr<View> view_;
	std::unique_ptr<Controller> controller_;
};



#endif /* SRC_GAME_GAMESTATE_H_ */
