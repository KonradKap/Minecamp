/*
 * GameState.cc
 *
 *  Created on: 1 cze 2016
 *      Author: konrad
 */

#include "GameState.h"
#include "GameStateEventType.h"

GameState::GameState(model_ptr model, view_ptr view, controller_ptr controller) :
	model_(std::move(model)),
	view_(std::move(view)),
	controller_(std::move(controller))
{
}

GameState::GameState(GameState&& state) :
	model_(std::move(state.model_)),
	view_(std::move(state.view_)),
	controller_(std::move(state.controller_))
{
}

GameState& GameState::operator= (GameState&& state)
{
	model_ = std::move(state.model_);
	view_ = std::move(state.view_);
	controller_ = std::move(state.controller_);
	return *this;
}

GameState::~GameState()
{
}
