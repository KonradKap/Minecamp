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

std::unique_ptr<GameState> GameStateFactory::getState(GameStateType type) const
{
	switch(type)
	{
	case GameStateType::MENU:
		return std::unique_ptr<GameState>(new Menu());
	case GameStateType::PLAY:
		return std::unique_ptr<GameState>(new Play());
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



