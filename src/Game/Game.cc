#include "Game/Game.h"

Game::Game() :
	state_(new Menu()),		//Menu is the default start
	view_(state_->getDefaultView())
{
	ofAddListener(state_->getEvent(), this, &Game::onStateSwitch);
}

Game::~Game()
{
}

///TODO: Make this reversible
///We want the ability to pause the Game
///Also keep in mind that GameState::Play is the heaviest of them all
///And thus it is not advised to reallocate it
void Game::update(float elapsed_time)
{
	state_->update(elapsed_time);
}

void Game::draw() const
{
	view_->draw();
}

void Game::onStateSwitch(const GameStateEventType& type)
{
	ofRemoveListener(state_->getEvent(), this, &Game::onStateSwitch);
	if(type == GameStateEventType::QUIT)
	{
		ofGetMainLoop()->shouldClose(0);
		return;
	}
	state_ = GameStateFactory::getInstance().getState(type);
	ofAddListener(state_->getEvent(), this, &Game::onStateSwitch);
	view_  = state_->getDefaultView();
}
