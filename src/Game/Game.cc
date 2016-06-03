#include "Game/Game.h"
#include "ofApp.h"

Game::Game() :
	Registrable(),
	state_()
{
	Registrable::registerMe();
	onGameStateEvent(GameStateEventType::SWITCH_TO_MENU); //Menu is the default start
}

Game::~Game()
{
	Registrable::unregisterMe();
}

void Game::registerMe(const do_register_trait&)
{
	ofAddListener(Model::getEvent(), this, &Game::onGameStateEvent);
}

void Game::unregisterMe(const do_register_trait&)
{
	ofRemoveListener(Model::getEvent(), this, &Game::onGameStateEvent);
}

void Game::onGameStateEvent(const GameStateEventType& type)
{
	switch(type)
	{
	case GameStateEventType::QUIT:
		onQuit();
		break;
	case GameStateEventType::SWITCH_TO_MENU:
		state_ = getMenu();
		break;
	case GameStateEventType::LOAD_STATE_1:
	case GameStateEventType::LOAD_STATE_2:
	case GameStateEventType::LOAD_STATE_3:
	case GameStateEventType::LOAD_STATE_4:
	case GameStateEventType::LOAD_STATE_5:
		state_ = getPlay(int(type));
		break;
	case GameStateEventType::PAUSE:
		state_ = getPause(state_);
		break;
	default:
		throw std::invalid_argument("Unknown GameEvent");
	}
}

void Game::onQuit() const
{
	ofGetMainLoop()->shouldClose(0);
}

GameState Game::getMenu() const
{
	std::unique_ptr<MenuModel> menu_model/* = std::make_unique<MenuModel>*/(new MenuModel());
	std::unique_ptr<MenuView>  menu_view/* = std::make_unique<MenuView>*/(new MenuView(*menu_model));
	std::unique_ptr<MenuController> menu_controller/* = std::make_unique<MenuController>*/(new MenuController(*menu_model));
	return GameState(std::move(menu_model), std::move(menu_view), std::move(menu_controller));
}

GameState Game::getPlay(int save) const
{
	std::unique_ptr<PlayModel> play_model/* = std::make_unique<PlayModel>*/(new PlayModel(save));
	std::unique_ptr<PlayView>  play_view/* = std::make_unique<PlayView>*/(new PlayView(*play_model));
	std::unique_ptr<PlayController> play_controller/* = std::make_unique<PlayController>*/(new PlayController(*play_model));
	return GameState(std::move(play_model), std::move(play_view), std::move(play_controller));
}

GameState Game::getPause(GameState& previous)
{
	//return;
}
