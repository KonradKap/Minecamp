/*
 * PlayerController.h
 *
 *  Created on: 1 cze 2016
 *      Author: konrad
 */

#ifndef SRC_PLAY_PLAYCONTROLLER_H_
#define SRC_PLAY_PLAYCONTROLLER_H_

#include "ofEvents.h"
#include "ofConstants.h"

class PlayModel;
#include "Game/Controller.h"
#include "Play/Player.h"

class PlayController : public Controller
{
public:
	PlayController(PlayModel& p);

	~PlayController();

	constexpr static const float MOUSE_SENSITIVITY = 0.15f;
private:
	enum TrackedButtons
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		COUNT
	};

	void onUpdate(ofEventArgs& parameter);

	void onMouseMove(ofMouseEventArgs& parameter);
	void onMousePress(ofMouseEventArgs& parameter);
	void onMouseRelease(ofMouseEventArgs& parameter);

	void onLeftMouseButtonPress();
	void onRightMouseButtonPress();

	void onKeyPressed(ofKeyEventArgs& parameter);
	void onKeyRelease(ofKeyEventArgs& parameter);

	PlayModel& model_;
	std::array<bool, TrackedButtons::COUNT> buttons_pressed_;
};

//#include "ofApp.h"



#endif /* SRC_PLAY_PLAYCONTROLLER_H_ */
