#include "Game/Game.h"

Game::Game() :
	state_(new Menu())		//Menu is the default start
{
}

Game::~Game()
{
	delete state_;
}
/*
void Game::handleInput()
{
	state_->handleInput();
}
*/
///TODO: Make this reversible using stack
///We want the ability to pause the Game
///Also keep in mind that GameState::Play is the heaviest of them all
///And thus it is not advised to reallocate it
bool Game::update(float elapsed_time)
{
	GameState* newState = state_->update(elapsed_time);
	if(newState == nullptr)
	{
		return false;
	}
	if(newState != state_)
	{
		delete state_;
		state_ = newState;
	}
	return true;
}

void Game::draw() const
{
	state_->draw();
}
