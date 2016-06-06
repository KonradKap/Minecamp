#include "Game/Game.h"
#include "ofApp.h"

ofEvent<void> Game::saveRequest_;

Game::Game() :
	Registrable(),
	states_()
{
	states_.push_back(createMenu(MenuModel::MenuState::MAIN)); //Menu is the default start
	Registrable::registerMe();
}

Game::~Game()
{
	Registrable::unregisterMe();
}

ofEvent<void>& Game::getSaveRequestEvent()
{
	return saveRequest_;
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
		states_.clear();
		states_.push_back(createMenu(MenuModel::MenuState::MAIN));
		break;
	case GameStateEventType::LOAD_STATE_1:
	case GameStateEventType::LOAD_STATE_2:
	case GameStateEventType::LOAD_STATE_3:
	case GameStateEventType::LOAD_STATE_4:
	case GameStateEventType::LOAD_STATE_5:
		states_.clear();
		states_.push_back(createPlay(int(type)));
		break;
	case GameStateEventType::PAUSE:
		states_.back().Registrable::unregisterMe();
		states_.push_back(createMenu(MenuModel::MenuState::PAUSE));
		break;
	case GameStateEventType::SAVE:
		for(auto& state : states_)
			state.Registrable::registerMe();

		Registrable::notify(getSaveRequestEvent());

		for(auto& state : states_)
			state.Registrable::unregisterMe();
		states_.back().Registrable::registerMe();
		break;
	case GameStateEventType::PAUSE_BREAK:
		states_.pop_back();
		states_.back().Registrable::registerMe();
		break;
	case GameStateEventType::RESET_OTHERS:
		states_.erase(states_.begin(), states_.end() - 1);
		break;
	default:
		throw std::invalid_argument("Unknown GameEvent");
	}
}

void Game::onQuit() const
{
	ofGetMainLoop()->shouldClose(0);
}

GameState Game::createMenu(MenuModel::MenuState state) const
{
	std::unique_ptr<MenuModel> menu_model(new MenuModel(state));
	std::unique_ptr<MenuView>  menu_view(new MenuView(*menu_model));
	std::unique_ptr<MenuController> menu_controller(new MenuController(*menu_model));
	return GameState(std::move(menu_model), std::move(menu_view), std::move(menu_controller));
}

GameState Game::createPlay(int save) const
{
	std::unique_ptr<PlayModel> play_model(new PlayModel(save));
	std::unique_ptr<PlayView>  play_view(new PlayView(*play_model));
	std::unique_ptr<PlayController> play_controller(new PlayController(*play_model));
	return GameState(std::move(play_model), std::move(play_view), std::move(play_controller));
}

