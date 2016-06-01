/*
 * PlayView.h
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_PLAYVIEW_H_
#define SRC_GAME_PLAYVIEW_H_

#include "World/World.h"
#include "ofEasyCam.h"
#include "ofCamera.h"
#include "ofx/ofxGameCamera.h"

#include "View.h"

class PlayView : public View
{
public:
	PlayView(const World& world);
	PlayView(const PlayView& pw);
	~PlayView();

	void draw();
private:

	const World& source_;
	mutable ofEasyCam cam_; //temporary
	mutable ofCamera camera_;
	mutable ofxGameCamera game_camera_;
};



#endif /* SRC_GAME_PLAYVIEW_H_ */
