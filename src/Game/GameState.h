/*
 * GameState.h
 *
 *  Created on: 10 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_GAMESTATE_H_
#define SRC_GAME_GAMESTATE_H_

#include <memory>

#include "GameStateEventType.h"
#include "ofEvents.h"

#include "Utill/View.h"

class GameState
{
public:
	GameState() : event_() {}
	virtual ~GameState() {}

	//virtual void handleInput() = 0;
	virtual void update(float elapsed_time) = 0;
	virtual std::unique_ptr<View> getDefaultView() const = 0;

	ofEvent<const GameStateEventType&>& getEvent() { return event_; }
private:
	ofEvent<const GameStateEventType&> event_;
};



#endif /* SRC_GAME_GAMESTATE_H_ */
