#include "Game/Game.h"
#include "ofApp.h"

Game::Game() :
	state_(GameStateFactory::getInstance().getState(GameStateEventType::SWITCH_TO_MENU))		//Menu is the default start
	//view_(state_->getDefaultView())
{
	ofAddListener(Model::getEvent(), this, &Game::onStateSwitch);
}

Game::~Game()
{
	ofRemoveListener(Model::getEvent(), this, &Game::onStateSwitch);
}

void Game::onStateSwitch(const GameStateEventType& type)
{
	if(type == GameStateEventType::QUIT)
	{
		ofGetMainLoop()->shouldClose(0);
		return;
	}
	state_ = GameStateFactory::getInstance().getState(type);
}
