/*
 * Menu.cc
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#include "MenuModel.h"
#include "ofApp.h"

const std::array<std::string, MenuModel::MenuButtonTitles::COUNT> MenuModel::TITLES_ =
 {"Play", "Quit", "Save One",
  "Save Two", "Save Three", "Save Four",
  "Save Five", "Return", "DEL",
  "Save and quit", "Quit without saving", "Resume game"};

MenuModel::MenuModel(MenuState starting_state) :
	Model(),
	state_(starting_state),
	background_(),
	title_(),
	wide_model_(),
	small_model_(),
	buttons_()
{
	setUpPaths();
	switchState(starting_state);
}

void MenuModel::setUpPaths()
{
	const MenuPathManager MANAGER;
	background_.load(MANAGER.get(MenuResources::BACKGROUND_T));
	title_.load(MANAGER.get(MenuResources::TITLE_T));
	wide_model_ = ButtonPrototypeLoader::getInstance().load(
			MANAGER.get(MenuResources::WIDE_BUTTON_D), MANAGER.get(MenuResources::FONT_F), FONT_SIZE);
	small_model_ = ButtonPrototypeLoader::getInstance().load(
			MANAGER.get(MenuResources::SMALL_BUTTON_D), MANAGER.get(MenuResources::FONT_F), FONT_SIZE);
}

void MenuModel::setUpButtons(const std::vector<std::string>& titles)
{
	const ofVec2f BUTTON_POSITION(ofApp::WINDOW_X_SIZE/2 - wide_model_.getSize().x/2, BUTTONSET_OFFSET);
	for(unsigned i = 0; i < titles.size(); ++i)
		buttons_.push_back(
				Button(BUTTON_POSITION + ofVec2f(0.0f, i*(BUTTON_OFFSET + wide_model_.getSize().y/2)), titles[i], wide_model_));

}

void MenuModel::setUpSmallButtons(const std::string& title)
{
	for(unsigned i = 0; i < SELECT_SMALL_BUTTON_COUNT; ++i)
		buttons_.push_back(
				Button(buttons_[i].getPosition()+ofVec2f(buttons_[i].getPrototype().getSize().x + BUTTON_OFFSET, 0), title, small_model_));

}

MenuModel::~MenuModel()
{
}

void MenuModel::registerMe(const do_register_trait&)
{
	for(auto& button : buttons_)
		ofAddListener(button.getEvent(), this, &MenuModel::onButtonPress);
}

void MenuModel::unregisterMe(const do_register_trait&)
{
	for(auto& button : buttons_)
		ofRemoveListener(button.getEvent(), this, &MenuModel::onButtonPress);
}

const ofImage& MenuModel::getBackground() const
{
	return background_;
}

const ofImage& MenuModel::getTitle() const
{
	return title_;
}

const std::vector<Button>& MenuModel::getButtons() const
{
	return buttons_;
}

void MenuModel::switchState(MenuState new_state)
{
	Registrable::unregisterMe();
	switch(new_state)
	{
	case MenuState::MAIN:
		switchToMain();
		break;
	case MenuState::LEVEL_SELECT:
		switchToLevelSelect();
		break;
	case MenuState::PAUSE:
		switchToPause();
		break;
	default:
		throw std::invalid_argument("No such menu state");
	}
	Registrable::registerMe();
}

void MenuModel::switchToMain()
{
	buttons_.clear();
	buttons_.reserve(MAIN_BUTTON_COUNT);
	setUpButtons({TITLES_[MenuButtonTitles::PLAY], TITLES_[MenuButtonTitles::QUIT]});
	state_ = MenuState::MAIN;
}

void MenuModel::switchToLevelSelect()
{
	buttons_.clear();
	buttons_.reserve(SELECT_BUTTON_COUNT);
	setUpButtons({TITLES_[MenuButtonTitles::SELECT_1], TITLES_[MenuButtonTitles::SELECT_2],
			      TITLES_[MenuButtonTitles::SELECT_3], TITLES_[MenuButtonTitles::SELECT_4],
				  TITLES_[MenuButtonTitles::SELECT_5], TITLES_[MenuButtonTitles::RETURN]});
	setUpSmallButtons(TITLES_[MenuButtonTitles::DELETE]);

	state_ = MenuState::LEVEL_SELECT;
}

void MenuModel::switchToPause()
{
	buttons_.clear();
	buttons_.reserve(PAUSE_BUTTON_COUNT);
	setUpButtons({TITLES_[MenuButtonTitles::SAVE_AND_QUIT],
				  TITLES_[MenuButtonTitles::NO_SAVE_QUIT],
				  TITLES_[MenuButtonTitles::RESUME]});

	state_ = MenuState::LEVEL_SELECT;
}

void MenuModel::onButtonPress(const Button& pressed)
{
	const int BUTTON_INDEX = std::distance(
			TITLES_.begin(), std::find(
					TITLES_.begin(), TITLES_.end(), pressed.getTitle()));
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
	case MenuButtonTitles::SAVE_AND_QUIT:
		onSaveAndQuitPressed();
		break;
	case MenuButtonTitles::NO_SAVE_QUIT:
		onNoSaveAndQuitPressed();
		break;
	case MenuButtonTitles::RESUME:
		onResumePressed();
		break;
	default:
		throw std::invalid_argument("Invalid button pressed");
	}
}

void MenuModel::onPlayPressed()
{
	switchState(MenuState::LEVEL_SELECT);
}

void MenuModel::onLevelSelect(const Button& pressed)
{
	const int SAVE_NUMBER = std::distance(
			buttons_.begin(), std::find_if(
					buttons_.begin(), buttons_.end(), [&pressed](const Button& b){
						return pressed.getPosition() == b.getPosition();
	}));
	Registrable::notify(Model::getEvent(), GameStateEventType(SAVE_NUMBER));
}

void MenuModel::onQuitPressed()
{
	if(state_ == MenuState::LEVEL_SELECT)
	{
		switchState(MenuState::MAIN);
		return;
	}
	Registrable::notify(getEvent(), GameStateEventType::QUIT);
}

void MenuModel::onLevelDeletion(const Button& pressed)
{
	const int SAVE_NUMBER = std::distance(
			buttons_.begin(), std::find_if(
					buttons_.begin(), buttons_.end(), [&pressed](const Button& b){
						return pressed.getPosition().y == b.getPosition().y;
	}));
	SaveFileManager::clear(SAVE_NUMBER);
}

void MenuModel::onSaveAndQuitPressed()
{
	Registrable::notify(Model::getEvent(), GameStateEventType::POP);
	Registrable::notify(Model::getEvent(), GameStateEventType::SAVE);
	Registrable::notify(Model::getEvent(), GameStateEventType::SWITCH_TO_MENU);
}

void MenuModel::onNoSaveAndQuitPressed()
{
	Registrable::notify(Model::getEvent(), GameStateEventType::POP);
	Registrable::notify(Model::getEvent(), GameStateEventType::SWITCH_TO_MENU);
}

void MenuModel::onResumePressed()
{
	Registrable::notify(Model::getEvent(), GameStateEventType::POP);
}

