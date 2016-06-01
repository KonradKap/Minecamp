/*
 * PlayerController.cc
 *
 *  Created on: 1 cze 2016
 *      Author: konrad
 */

#include "PlayController.h"
#include "Play/PlayModel.h"
#include "ofAppGLFWWindow.h"

PlayController::PlayController(PlayModel& p) :
	Controller(),
	model_(p)
{
	ofAddListener(ofEvents().update, this, &PlayController::onUpdate);
	ofAddListener(ofEvents().mouseMoved, this, &PlayController::onMouseMove);
	ofAddListener(ofEvents().mousePressed, this, &PlayController::onMousePress);
	ofAddListener(ofEvents().mouseReleased, this, &PlayController::onMouseRelease);
	ofAddListener(ofEvents().mouseDragged, this, &PlayController::onMouseMove);
	ofAddListener(ofEvents().keyPressed, this, &PlayController::onKeyPressed);
	ofAddListener(ofEvents().keyReleased, this, &PlayController::onKeyRelease);
}

PlayController::~PlayController()
{
	ofRemoveListener(ofEvents().update, this, &PlayController::onUpdate);
	ofRemoveListener(ofEvents().mouseMoved, this, &PlayController::onMouseMove);
	ofRemoveListener(ofEvents().mousePressed, this, &PlayController::onMousePress);
	ofRemoveListener(ofEvents().mouseReleased, this, &PlayController::onMouseRelease);
	ofRemoveListener(ofEvents().mouseDragged, this, &PlayController::onMouseMove);
	ofRemoveListener(ofEvents().keyPressed, this, &PlayController::onKeyPressed);
	ofRemoveListener(ofEvents().keyReleased, this, &PlayController::onKeyRelease);
}

void PlayController::onUpdate(ofEventArgs& parameter)
{

	vec3Di direction;
	for(unsigned i = 0; i < buttons_pressed_.size(); ++i)
		if(buttons_pressed_[i])
			direction += vec3Di::make_unit_vector(Side(i));

	model_.getPlayer().applyDirection(direction);
}

void PlayController::onMouseMove(ofMouseEventArgs& parameter)
{
	//std::cout << parameter << std::endl;
	model_.getPlayer().horizontalRotate((ofGetWindowWidth()/2-parameter.x)*MOUSE_SENSITIVITY);
	model_.getPlayer().verticalRotate((ofGetWindowHeight()/2-parameter.y)*MOUSE_SENSITIVITY);
	//ofGet
	GLFWwindow* window = static_cast<GLFWwindow*>(ofGetWindowPtr()->getWindowContext());
	glfwSetCursorPos(window, ofGetWindowWidth()/2 ,ofGetWindowHeight()/2);
}

void PlayController::onMousePress(ofMouseEventArgs& parameter)
{
}

void PlayController::onMouseRelease(ofMouseEventArgs& parameter)
{
}

void PlayController::onKeyPressed(ofKeyEventArgs& parameter)
{
	switch(parameter.key)
	{
	case 'w':
		buttons_pressed_[UP] = true;
		break;
	case 's':
		buttons_pressed_[DOWN] = true;
		break;
	case 'a':
		buttons_pressed_[LEFT] = true;
		break;
	case 'd':
		buttons_pressed_[RIGHT] = true;
		break;
	}
}

void PlayController::onKeyRelease(ofKeyEventArgs& parameter)
{
	switch(parameter.key)
	{
	case 'w':
		buttons_pressed_[UP] = false;
		break;
	case 's':
		buttons_pressed_[DOWN] = false;
		break;
	case 'a':
		buttons_pressed_[LEFT] = false;
		break;
	case 'd':
		buttons_pressed_[RIGHT] = false;
		break;
	}
}


