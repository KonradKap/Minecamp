/*
 * Menu.cc
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#include "Menu/Menu.h"

Menu::Menu() :
	GameState(),
	background_(),
	title_(),
	model_(),
	buttons_({Button(ofVec2f(0, 0), "Play", &model_),
			  Button(ofVec2f(0, 0), "Quit", &model_)})
{
	const MenuPathManager MANAGER;
	background_.load(MANAGER.get(MenuResources::BACKGROUND_T));
	title_.load(MANAGER.get(MenuResources::TITLE_T));
	model_ = ButtonModel(MANAGER.get(MenuResources::BUTTON_D), MANAGER.get(MenuResources::FONT_F), FONT_SIZE);

	const ofVec2f BUTTON_POSITION(ofApp::WINDOW_X_SIZE/2 - model_.getSize().x/2, BUTTONSET_OFFSET);
	buttons_[unsigned(ButtonType::PLAY)].setPosition(BUTTON_POSITION);
	buttons_[unsigned(ButtonType::QUIT)].setPosition(BUTTON_POSITION + ofVec2f(0.0f, BUTTON_OFFSET + model_.getSize().y/2));
	ofAddListener(buttons_[unsigned(ButtonType::PLAY)].getEvent(), this, &Menu::onPlayPressed);
	ofAddListener(buttons_[unsigned(ButtonType::QUIT)].getEvent(), this, &Menu::onQuitPressed);
}

Menu::~Menu()
{
}
//TODO: Buttons, switching states to Play, Load, Options etc.
//Recieving messages from buttons
//Maybe use listener pattern to send messages to game
void Menu::update(float elapsed_time)
{
	/*
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
	*/
}

const ofImage& Menu::getBackground() const
{
	return background_;
}

const ofImage& Menu::getTitle() const
{
	return title_;
}

const Button& Menu::getButton(const ButtonType type) const
{
	return buttons_[unsigned(type)];
}

std::unique_ptr<View> Menu::getDefaultView() const
{
	return std::unique_ptr<View>(new MenuView(*this));
}

void Menu::onPlayPressed()
{
	GameStateType play = GameStateType::PLAY;
	ofNotifyEvent(GameState::getEvent(), play, this);
}

void Menu::onQuitPressed()
{
	GameStateType quit = GameStateType::QUIT;
	ofNotifyEvent(GameState::getEvent(), quit, this);
}


