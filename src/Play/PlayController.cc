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
}

PlayController::~PlayController()
{
}

void PlayController::registerMe(const do_register_trait&)
{
	ofAddListener(ofEvents().update, this, &PlayController::onUpdate);
	ofAddListener(ofEvents().mouseMoved, this, &PlayController::onMouseMove);
	ofAddListener(ofEvents().mousePressed, this, &PlayController::onMousePress);
	ofAddListener(ofEvents().mouseDragged, this, &PlayController::onMouseMove);
	//ofAddListener(ofEvents().keyPressed, this, &PlayController::onKeyPressed);
	ofAddListener(ofEvents().keyReleased, this, &PlayController::onKeyRelease);
	ofAddListener(ofEvents().mouseScrolled, this, &PlayController::onMouseScroll);
}

void PlayController::unregisterMe(const do_register_trait&)
{
	ofRemoveListener(ofEvents().update, this, &PlayController::onUpdate);
	ofRemoveListener(ofEvents().mouseMoved, this, &PlayController::onMouseMove);
	ofRemoveListener(ofEvents().mousePressed, this, &PlayController::onMousePress);
	ofRemoveListener(ofEvents().mouseDragged, this, &PlayController::onMouseMove);
	//ofRemoveListener(ofEvents().keyPressed, this, &PlayController::onKeyPressed);
	ofRemoveListener(ofEvents().keyReleased, this, &PlayController::onKeyRelease);
	ofRemoveListener(ofEvents().mouseScrolled, this, &PlayController::onMouseScroll);
}

void PlayController::onUpdate(ofEventArgs& parameter)
{
	std::array<bool, TrackedButtons::COUNT> buttons_pressed =
	{ofGetKeyPressed('w'), ofGetKeyPressed('s'), ofGetKeyPressed('a'), ofGetKeyPressed('d')};

	vec3Di direction;
	for(unsigned i = 0; i < buttons_pressed.size(); ++i)
		if(buttons_pressed[i])
			direction += vec3Di::make_unit_vector(Side(i));

	model_.getPlayer().setSteer(direction);
}

void PlayController::onMouseMove(ofMouseEventArgs& parameter)
{
	model_.getPlayer().horizontalRotate((ofGetWindowWidth()/2-parameter.x)*MOUSE_SENSITIVITY);
	model_.getPlayer().verticalRotate((ofGetWindowHeight()/2-parameter.y)*MOUSE_SENSITIVITY);

	GLFWwindow* window = static_cast<GLFWwindow*>(ofGetWindowPtr()->getWindowContext());
	glfwSetCursorPos(window, ofGetWindowWidth()/2 ,ofGetWindowHeight()/2);
}

void PlayController::onMousePress(ofMouseEventArgs& parameter)
{
	switch(parameter.button)
	{
	case OF_MOUSE_BUTTON_1:
		onMouseButtonPress([](const std::pair<vec3Di, vec3Di>& arg){return arg.first;},
						   [](){return BlockType::AIR;});
		break;
	case OF_MOUSE_BUTTON_3:
		onMouseButtonPress([](const std::pair<vec3Di, vec3Di>& arg){return arg.second;},
						   [&](){return model_.getEquipmentManager().getCurrentChoice();});
		break;
	}
}

void PlayController::onMouseButtonPress(
		const std::function<vec3Di (const std::pair<vec3Di, vec3Di>&)>& getBlockPosition,
		const std::function<BlockType ()>& getBlockType)
{
	auto target = model_.findTargetedBlock();
	if(!model_.getWorldManager().isWithin(target.first))
		return;
	Registrable::notify(model_.getWorldManager().getBlockEvent(),
		std::make_pair(getBlockPosition(target), getBlockType()));
}

void PlayController::onMouseScroll(ofMouseEventArgs& parameter)
{
	if(parameter.scrollY > 0)
		model_.getEquipmentManager().prev();
	else
		model_.getEquipmentManager().next();
}
/*
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
	case OF_KEY_ESC:
		Registrable::notify(model_.getEvent(), GameStateEventType::PAUSE);
		break;
	}
}
*/
void PlayController::onKeyRelease(ofKeyEventArgs& parameter)
{
	if(parameter.key == OF_KEY_ESC)
		Registrable::notify(model_.getEvent(), GameStateEventType::PAUSE);
}



