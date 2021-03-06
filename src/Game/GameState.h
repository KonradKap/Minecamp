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

#include "Game/View.h"
#include "Game/Controller.h"
#include "Game/Model.h"

#include "Utill/Registrable.h"

class GameState : public Registrable
{
public:
	typedef std::unique_ptr<View> view_ptr;
	typedef std::unique_ptr<Model> model_ptr;
	typedef std::unique_ptr<Controller> controller_ptr;

	GameState();
	GameState(model_ptr model, view_ptr view, controller_ptr controller);
	GameState(GameState&& state);
	GameState& operator= (GameState&& state);

	const view_ptr& getView() const;
	const model_ptr& getModel() const;
	const controller_ptr& getController() const;

	~GameState();

private:
	void registerMe(const do_register_trait&);
	void unregisterMe(const do_register_trait&);

	std::unique_ptr<Model> model_;
	std::unique_ptr<View> view_;
	std::unique_ptr<Controller> controller_;
};


#endif /* SRC_GAME_GAMESTATE_H_ */
