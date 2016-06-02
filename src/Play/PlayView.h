/*
 * PlayView.h
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_PLAYVIEW_H_
#define SRC_GAME_PLAYVIEW_H_

class PlayModel;

#include "ofEasyCam.h"
#include "ofCamera.h"
#include "ofQuaternion.h"

//#include "ofx/ofxGameCamera.h"

#include "Game/View.h"

class PlayView : public View
{
public:
	PlayView(const PlayModel& model);
	PlayView(const PlayView& pw);
	~PlayView();


private:
	void setup();

	void onUpdate(ofEventArgs&);
	void onDraw(ofEventArgs&);

	const PlayModel& source_;
	mutable ofEasyCam cam_; //temporary
	mutable ofCamera camera_;

	//mutable ofxGameCamera game_camera_;
};



#endif /* SRC_GAME_PLAYVIEW_H_ */
