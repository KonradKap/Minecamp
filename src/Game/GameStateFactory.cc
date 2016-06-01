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

GameState GameStateFactory::getState(GameStateEventType type) const
{
	switch(type)
	{
	case GameStateEventType::SWITCH_TO_MENU:
		return getMenu();
	case GameStateEventType::LOAD_STATE_1:
	case GameStateEventType::LOAD_STATE_2:
	case GameStateEventType::LOAD_STATE_3:
	case GameStateEventType::LOAD_STATE_4:
	case GameStateEventType::LOAD_STATE_5:
		return getPlay(int(type));
	default:
		throw std::invalid_argument("Unknown GameEvent");
	}
}

GameState GameStateFactory::getMenu() const
{
	std::unique_ptr<MenuModel> menu_model/* = std::make_unique<MenuModel>*/(new MenuModel());
	std::unique_ptr<MenuView>  menu_view/* = std::make_unique<MenuView>*/(new MenuView(*menu_model));
	std::unique_ptr<MenuController> menu_controller/* = std::make_unique<MenuController>*/(new MenuController(*menu_model));
	return GameState(std::move(menu_model), std::move(menu_view), std::move(menu_controller));
}

GameState GameStateFactory::getPlay(int save) const
{
	std::unique_ptr<PlayModel> play_model/* = std::make_unique<PlayModel>*/(new PlayModel(save));
	std::unique_ptr<PlayView>  play_view/* = std::make_unique<PlayView>*/(new PlayView(*play_model));
	std::unique_ptr<PlayController> play_controller/* = std::make_unique<PlayController>*/(new PlayController(*play_model));
	return GameState(std::move(play_model), std::move(play_view), std::move(play_controller));
}

GameStateFactory::~GameStateFactory()
{

}

GameStateFactory::GameStateFactory()
{

}



