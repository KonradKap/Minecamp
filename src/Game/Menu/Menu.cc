/*
 * Menu.cc
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#include "Game/Menu/Menu.h"

Menu::Menu() :
	GameState(),
	chosen_option_(NOTHING),
	background_(),
	title_(),
	model_(),
	play_button_(ofVec2f(0, 0), "Play", &model_),
	quit_button_(ofVec2f(0, 0), "Quit", &model_)
{
	const MenuPathManager MANAGER;
	background_.load(MANAGER.get(MenuResources::BACKGROUND_T));
	title_.load(MANAGER.get(MenuResources::TITLE_T));
	model_.setup(MANAGER.get(MenuResources::BUTTON_D), MANAGER.get(MenuResources::FONT_F), FONT_SIZE);

	const ofVec2f BUTTON_POSITION(ofApp::WINDOW_X_SIZE/2 - model_.getSize().x/2, BUTTONSET_OFFSET);
	play_button_.setPosition(BUTTON_POSITION);
	quit_button_.setPosition(BUTTON_POSITION + ofVec2f(0.0f, BUTTON_OFFSET + model_.getSize().y/2));
	ofAddListener(play_button_.pressed, this, &Menu::onPlayPressed);
	ofAddListener(quit_button_.pressed, this, &Menu::onQuitPressed);
}

Menu::~Menu()
{
}
//TODO: Buttons, switching states to Play, Load, Options etc.
//Recieving messages from buttons
//Maybe use listener pattern to send messages to game?
GameState* Menu::update(float elapsed_time)
{
	switch(chosen_option_)
	{
	case NOTHING:
		return this;
	case PLAY:
		return new Play();
	case QUIT:
		return nullptr;
	default:
		return nullptr;
	}
}
/*
void Menu::handleInput()
{
}
*/
void Menu::draw() const
{
	background_.draw(0, 0, ofApp::WINDOW_X_SIZE, ofApp::WINDOW_Y_SIZE);
	title_.draw(ofApp::WINDOW_X_SIZE/2 - title_.getWidth()/2, TITLE_OFFSET);
	play_button_.draw();
	quit_button_.draw();
}

void Menu::onPlayPressed()
{
	chosen_option_ = PLAY;
}

void Menu::onQuitPressed()
{
	chosen_option_ = QUIT;
}


