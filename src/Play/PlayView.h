/*
 * PlayView.h
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_PLAYVIEW_H_
#define SRC_GAME_PLAYVIEW_H_

#include "ofEasyCam.h"

#include "View.h"
#include "World/World.h"

class PlayView : public View
{
public:
	PlayView(const World& world);
	PlayView(const PlayView& pw);
	~PlayView();

	void draw() const;
private:
	const World& source_;
	mutable ofEasyCam cam_; //temporary
};



#endif /* SRC_GAME_PLAYVIEW_H_ */
