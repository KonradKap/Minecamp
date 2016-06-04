/*
 * GameState.cc
 *
 *  Created on: 1 cze 2016
 *      Author: konrad
 */

#include "GameState.h"
#include "GameStateEventType.h"

GameState::GameState() :
	Registrable(),
	model_(),
	view_(),
	controller_()
{
	Registrable::registerMe();
}

GameState::GameState(model_ptr model, view_ptr view, controller_ptr controller) :
	Registrable(),
	model_(std::move(model)),
	view_(std::move(view)),
	controller_(std::move(controller))
{
	Registrable::registerMe();
}

GameState::GameState(GameState&& state) :
	Registrable(),
	model_(std::move(state.model_)),
	view_(std::move(state.view_)),
	controller_(std::move(state.controller_))
{
	Registrable::registerMe();
}

void GameState::registerMe(const do_register_trait&)
{
	if(!model_ or !view_ or !controller_)
		return;
	model_->Registrable::registerMe();
	view_->Registrable::registerMe();
	controller_->Registrable::registerMe();
}

void GameState::unregisterMe(const do_register_trait&)
{
	if(!model_ or !view_ or !controller_)
		return;
	model_->Registrable::unregisterMe();
	view_->Registrable::unregisterMe();
	controller_->Registrable::unregisterMe();
}

GameState& GameState::operator= (GameState&& state)
{
	model_ = std::move(state.model_);
	view_ = std::move(state.view_);
	controller_ = std::move(state.controller_);
	return *this;
}

const GameState::view_ptr& GameState::getView() const
{
	return view_;
}

const GameState::model_ptr& GameState::getModel() const
{
	return model_;
}

const GameState::controller_ptr& GameState::getController() const
{
	return controller_;
}

GameState::~GameState()
{
	Registrable::unregisterMe();
}
