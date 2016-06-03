/*
 * Pause.cc
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */

#include "PauseModel.h"
#include "ofApp.h"

PauseModel::PauseModel(GameState previousState) :
	Model(),
	prototype_(),
	buttons_({Button(ofVec2f(), "", prototype_),
			  Button(ofVec2f(), "", prototype_),
			  Button(ofVec2f(), "", prototype_)}),
	background_(),
	previousState_(std::move(previousState))
{
	setupPaths();
	setupButtons();
	Registrable::registerMe();
}

PauseModel::~PauseModel()
{
}

void PauseModel::registerMe(const do_register_trait&)
{
	previousState_.Registrable::unregisterMe();
	for(auto button : buttons_)
		ofAddListener(button.getEvent(), this, &PauseModel::onButtonPress);
}

void PauseModel::unregisterMe(const do_register_trait&)
{
	previousState_.Registrable::registerMe();
	for(auto button : buttons_)
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
		buttons_[i].setPosition(BUTTON_POSITION + ofVec2f(0, i * BUTTON_OFFSET_Y));
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

}
