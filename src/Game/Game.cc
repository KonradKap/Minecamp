#include "Game/Game.h"
#include "ofApp.h"

Game::Game() :
	Registrable(),
	stateStack_()
{
	stateStack_.push(getMenu(MenuModel::MenuState::MAIN)); //Menu is the default start
	Registrable::registerMe();
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
		//if(!stateStack_.empty())
		stateStack_.pop();
		stateStack_.push(getMenu(MenuModel::MenuState::MAIN));
		break;
	case GameStateEventType::LOAD_STATE_1:
	case GameStateEventType::LOAD_STATE_2:
	case GameStateEventType::LOAD_STATE_3:
	case GameStateEventType::LOAD_STATE_4:
	case GameStateEventType::LOAD_STATE_5:
		stateStack_.pop();
		stateStack_.push(getPlay(int(type)));
		break;
	case GameStateEventType::PAUSE:
		stateStack_.top().Registrable::unregisterMe();
		stateStack_.push(getMenu(MenuModel::MenuState::PAUSE));
		break;
	case GameStateEventType::SAVE:
		static_cast<const PlayModel*>(stateStack_.top().getModel().get())->save();
		break;
	case GameStateEventType::POP:
		stateStack_.pop();
		stateStack_.top().Registrable::registerMe();
		break;
	default:
		throw std::invalid_argument("Unknown GameEvent");
	}
}

void Game::onQuit() const
{
	ofGetMainLoop()->shouldClose(0);
}

GameState Game::getMenu(MenuModel::MenuState state) const
{
	std::unique_ptr<MenuModel> menu_model(new MenuModel(state));
	std::unique_ptr<MenuView>  menu_view(new MenuView(*menu_model));
	std::unique_ptr<MenuController> menu_controller(new MenuController(*menu_model));
	return GameState(std::move(menu_model), std::move(menu_view), std::move(menu_controller));
}

GameState Game::getPlay(int save) const
{
	std::unique_ptr<PlayModel> play_model(new PlayModel(save));
	std::unique_ptr<PlayView>  play_view(new PlayView(*play_model));
	std::unique_ptr<PlayController> play_controller(new PlayController(*play_model));
	return GameState(std::move(play_model), std::move(play_view), std::move(play_controller));
}

