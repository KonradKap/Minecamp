/*
 * Pause.cc
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */

#include "PauseModel.h"
#include "ofApp.h"

PauseModel::PauseModel(/*GameState previousState*/) :
	Model(),
	prototype_(),
	buttons_({Button(ofVec2f(), "", prototype_),
			  Button(ofVec2f(), "", prototype_),
			  Button(ofVec2f(), "", prototype_)}),
	background_()
{
	setupPaths();
	setupButtons();
}

PauseModel::~PauseModel()
{
}

void PauseModel::registerMe(const do_register_trait&)
{
	for(auto& button : buttons_)
		ofAddListener(button.getEvent(), this, &PauseModel::onButtonPress);
}

void PauseModel::unregisterMe(const do_register_trait&)
{
	for(auto& button : buttons_)
		ofRemoveListener(button.getEvent(), this, &PauseModel::onButtonPress);
}

void PauseModel::setupPaths()
{
	const PausePathManager MANAGER;
		prototype_ = ButtonPrototype(MANAGER.get(PauseResources::BUTTON_D), MANAGER.get(PauseResources::FONT_F), FONT_SIZE);
		background_.load(MANAGER.get(PauseResources::BACKGROUND_T));
}

void PauseModel::setupButtons()
{
	const ofVec2f BUTTON_POSITION(ofApp::WINDOW_X_SIZE/2 - prototype_.getSize().x/2, float(BUTTON_SET_Y));
	const std::array<std::string, int(ButtonType::COUNT)> TITLES = {"Save and quit", "Quit without saving", "Resume game"};
	for(int i = 0; i < int(ButtonType::COUNT); ++i)
	{
		buttons_[i].setPosition(BUTTON_POSITION + ofVec2f(0, i * (BUTTON_OFFSET_Y + buttons_[i].getPrototype().getSize().y)));
		buttons_[i].setTitle(TITLES[i]);
	}
}

const std::array<Button, unsigned(PauseModel::ButtonType::COUNT)>& PauseModel::getButtons() const
{
	return buttons_;
}

const ofImage& PauseModel::getBackground() const
{
	return background_;
}

void PauseModel::onButtonPress(const Button& b)
{
	const int CHOSEN_OPTION = std::distance(
			buttons_.begin(), std::find_if(
					buttons_.begin(), buttons_.end(), [&b](const Button& looked){
						return b.getPosition() == looked.getPosition();
	}));

	Registrable::notify(Model::getEvent(), GameStateEventType::POP);

	if(ButtonType(CHOSEN_OPTION) == ButtonType::SAVE_AND_QUIT)
		Registrable::notify(Model::getEvent(), GameStateEventType::SAVE);

	if(ButtonType(CHOSEN_OPTION) == ButtonType::SAVE_AND_QUIT or
	   ButtonType(CHOSEN_OPTION) == ButtonType::NO_SAVE_QUIT)
		Registrable::notify(Model::getEvent(), GameStateEventType::SWITCH_TO_MENU);

}
