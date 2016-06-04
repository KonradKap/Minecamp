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
	void registerMe(const do_register_trait&);
	void unregisterMe(const do_register_trait&);

	void onUpdate(ofEventArgs& parameter);

	void onMouseMove(ofMouseEventArgs& parameter);
	void onMousePress(ofMouseEventArgs& parameter);
	void onMouseRelease(ofMouseEventArgs& parameter);

	void onMouseScroll(ofMouseEventArgs& parameter);

	void onLeftMouseButtonPress();
	void onRightMouseButtonPress();

	void onMouseButtonPress(const std::function<vec3Di (const std::pair<vec3Di, vec3Di>&)>& getBlockPosition,
							const std::function<BlockType ()>& getBlockType);

	//void onKeyPressed(ofKeyEventArgs& parameter);
	void onKeyRelease(ofKeyEventArgs& parameter);



	PlayModel& model_;
	//std::array<bool, TrackedButtons::COUNT> buttons_pressed_;
};

//#include "ofApp.h"



#endif /* SRC_PLAY_PLAYCONTROLLER_H_ */
