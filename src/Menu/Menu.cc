/*
 * Menu.cc
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#include "Menu/Menu.h"

Menu::Menu() :
	GameState(),
	state_(MenuState::MAIN),
	TITLES_({"Play", "Quit", "Save One",
			"Save Two", "Save Three", "Save Four",
			"Save Five", "Return", "DEL"}),
	background_(),
	title_(),
	wide_model_(),
	small_model_(),
	buttons_()
{
	setUpPaths();
	switchToMain();
}

void Menu::setUpPaths()
{
	const MenuPathManager MANAGER;
	background_.load(MANAGER.get(MenuResources::BACKGROUND_T));
	title_.load(MANAGER.get(MenuResources::TITLE_T));
	wide_model_ = ButtonModel(MANAGER.get(MenuResources::WIDE_BUTTON_D), MANAGER.get(MenuResources::FONT_F), FONT_SIZE);
	small_model_ = ButtonModel(MANAGER.get(MenuResources::SMALL_BUTTON_D), MANAGER.get(MenuResources::FONT_F), FONT_SIZE);
}

void Menu::setUpButtons(const std::vector<std::string>& titles)
{
	const ofVec2f BUTTON_POSITION(ofApp::WINDOW_X_SIZE/2 - wide_model_.getSize().x/2, BUTTONSET_OFFSET);
	for(unsigned i = 0; i < titles.size(); ++i)
	{
		buttons_.push_back(
				Button(BUTTON_POSITION + ofVec2f(0.0f, i*(BUTTON_OFFSET + wide_model_.getSize().y/2)), titles[i], &wide_model_));
		ofAddListener(buttons_.back().getEvent(), this, &Menu::onButtonPress);
	}
}

void Menu::setUpSmallButtons(const std::string& title)
{
	//const unsigned SMALL_BUTTON_COUNT = SELECT_BUTTON_COUNT - buttons_.size();
	for(unsigned i = 0; i < SELECT_SMALL_BUTTON_COUNT; ++i)
	{
		buttons_.push_back(
				Button(buttons_[i].getPosition()+ofVec2f(buttons_[i].getModel()->getSize().x + BUTTON_OFFSET, 0), title, &small_model_));
		ofAddListener(buttons_.back().getEvent(), this, &Menu::onButtonPress);
	}
}

Menu::~Menu()
{
}

void Menu::update(float elapsed_time)
{
}

const ofImage& Menu::getBackground() const
{
	return background_;
}

const ofImage& Menu::getTitle() const
{
	return title_;
}

const std::vector<Button>& Menu::getButtons() const
{
	return buttons_;
}

std::unique_ptr<View> Menu::getDefaultView() const
{
	return std::unique_ptr<View>(new MenuView(*this));
}

void Menu::switchState(MenuState new_state)
{
	switch(new_state)
	{
	case MenuState::MAIN:
		switchToMain();
		break;
	case MenuState::LEVEL_SELECT:
		switchToLevelSelect();
		break;
	default:
		throw std::invalid_argument("No such menu state");
	}
}

void Menu::switchToMain()
{
	if(state_ == MenuState::LEVEL_SELECT)
	{
		for(auto& it : buttons_)
			ofRemoveListener(it.getEvent(), this, &Menu::onButtonPress);
	}

	buttons_.clear();
	buttons_.reserve(MAIN_BUTTON_COUNT);
	setUpButtons({TITLES_[MenuButtonTitles::PLAY], TITLES_[MenuButtonTitles::QUIT]});

	state_ = MenuState::MAIN;
}

void Menu::switchToLevelSelect()
{
	for(auto& it : buttons_)
		ofRemoveListener(it.getEvent(), this, &Menu::onButtonPress);

	buttons_.clear();
	buttons_.reserve(SELECT_BUTTON_COUNT);
	setUpButtons({TITLES_[MenuButtonTitles::SELECT_1], TITLES_[MenuButtonTitles::SELECT_2],
			      TITLES_[MenuButtonTitles::SELECT_3], TITLES_[MenuButtonTitles::SELECT_4],
				  TITLES_[MenuButtonTitles::SELECT_5], TITLES_[MenuButtonTitles::RETURN]});

	setUpSmallButtons("DEL");

	state_ = MenuState::LEVEL_SELECT;
}

void Menu::onButtonPress(const Button& pressed)
{
	const int BUTTON_INDEX = std::distance(TITLES_.begin(), std::find(TITLES_.begin(), TITLES_.end(), pressed.getTitle()));
	switch(BUTTON_INDEX)
	{
	case MenuButtonTitles::PLAY:
		onPlayPressed();
		break;
	case MenuButtonTitles::QUIT:
	case MenuButtonTitles::RETURN:
		onQuitPressed();
		break;
	case MenuButtonTitles::SELECT_1:
	case MenuButtonTitles::SELECT_2:
	case MenuButtonTitles::SELECT_3:
	case MenuButtonTitles::SELECT_4:
	case MenuButtonTitles::SELECT_5:
		onLevelSelect(pressed);
		break;
	case MenuButtonTitles::DELETE:
		onLevelDeletion(pressed);
		break;
	default:
		throw std::invalid_argument("Invalid button pressed");
	}
}

void Menu::onPlayPressed()
{
	switchState(MenuState::LEVEL_SELECT);
}

void Menu::onLevelSelect(const Button& pressed)
{
	int save_number = std::distance(buttons_.begin(), std::find_if(buttons_.begin(), buttons_.end(),
			[pressed](const Button& b){return pressed.getTitle() == b.getTitle();}));
	ofNotifyEvent(GameState::getEvent(), GameStateEventType(save_number), this);
}

void Menu::onQuitPressed()
{
	if(state_ == MenuState::LEVEL_SELECT)
	{
		switchState(MenuState::MAIN);
		return;
	}
	ofNotifyEvent(GameState::getEvent(), GameStateEventType::QUIT, this);
}

void Menu::onLevelDeletion(const Button& pressed)
{
	int save_number = std::distance(buttons_.begin(), std::find_if(buttons_.begin(), buttons_.end(),
			[pressed](const Button& b){return pressed.getPosition().y == b.getPosition().y;}));
	SaveFileManager::clear(save_number);
}

