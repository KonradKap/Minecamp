/*
 * GameStateFactory.cc
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#include "Game/GameStateFactory.h"

GameStateFactory& GameStateFactory::getInstance()
{
	static GameStateFactory instance;
	return instance;
}

std::unique_ptr<GameState> GameStateFactory::getState(GameStateEventType type) const
{
	switch(type)
	{
	case GameStateEventType::SWITCH_TO_MENU:
		return std::unique_ptr<GameState>(new Menu());
	case GameStateEventType::LOAD_STATE_1:
	case GameStateEventType::LOAD_STATE_2:
	case GameStateEventType::LOAD_STATE_3:
	case GameStateEventType::LOAD_STATE_4:
	case GameStateEventType::LOAD_STATE_5:
		return std::unique_ptr<GameState>(new Play(int(type)));
	default:
		throw std::invalid_argument("Unknown GameState");
	}
}

GameStateFactory::~GameStateFactory()
{

}

GameStateFactory::GameStateFactory()
{

}



